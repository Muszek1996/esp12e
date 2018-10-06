//
// Created by Jakub on 04.10.2018.
//
#include <WebSocketsServer.h>
#include "LinkedList.h"
#include "../TempSensor/TempSensor.h"
#include "../Actuator/Actuator.h"
#include <Arduino.h>
#include <ArduinoJson.h>

#ifndef NEWNODE_WEBSOCKETS_H
#define NEWNODE_WEBSOCKETS_H

namespace WebSocket {
    static WebSocketsServer webSocketsServer(81);
    static LinkedList<uint8_t> *clients = new LinkedList<uint8_t>();

    static void webSocketLoop() {
        webSocketsServer.loop();
    }

   static void handleDataReceived(uint8_t num, uint8_t *payload, size_t lenght) {
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(payload);
        WebSocket::webSocketsServer.sendTXT(num, payload);
        if (root.containsKey("type")) {
            if (root["type"] == "tempOnSlider") {
                double tempReceived = root["data"];
                TempSensor::setTargetTemp(tempReceived);
            } else if (root["type"] == "speedOnSlider") {
                int speedReceived = root["data"];
                Actuator::setSpeed(speedReceived);
            } else if (root["type"] == "windowAction") {
                if (root["data"] == "0") {
                    Actuator::close();
                } else if (root["data"] == "1") {
                    Actuator::open();
                } else {
                    Actuator::stop();
                }
            }

        }
    }

    static void getTemps(){
        TempSensor::getTemps();
    }

    static void reportTemperatures() {
        StaticJsonBuffer<150> jsonBuffer;
        JsonObject &root = jsonBuffer.createObject();
        root["type"] = "TempSensorReadings";
        root["tempSlider"] = TempSensor::getTargetTemp();
        root["speedSlider"] = Actuator::getSpeed();
        JsonArray &array = root.createNestedArray("data");
        for (int i = 0; i < WebSocket::clients->size(); i++) {
            char msg[150];
            for (int j = 0; j < TempSensor::getICsQuantity(); j++) {
                array.add((TempSensor::getLastTemps())[j]);
            }
            root.printTo(msg);
            WebSocket::webSocketsServer.sendTXT(WebSocket::clients->get(i), msg);
        }
    }


    void static webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload,
                               size_t lenght) { // When a WebSocket message is received
        switch (type) {
            case WStype_DISCONNECTED:             // if the websocket is disconnected
                Serial.printf("[%u] Disconnected!\n", num);
                for (int i = 0; i < clients->size(); i++) {
                    if (clients->get(i) == num) {
                        clients->remove(i);
                    }
                }
                break;
            case WStype_CONNECTED: {              // if a new websocket connection is established
                clients->add(num);
                IPAddress ip = webSocketsServer.remoteIP(num);
                char msg[50];
                sprintf(msg, "[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
                StaticJsonBuffer<100> jsonBuffer;
                JsonObject &root = jsonBuffer.createObject();
                root["type"] = "Data";
                root["data"] = msg;
                String a;
                root.printTo(a);
                webSocketsServer.sendTXT(num, a);
            }
                break;
            case WStype_TEXT: {                   // if new text data is received
                handleDataReceived(num, payload, lenght);
            }
        }
    }


    static void startWebSocket() { // Start a WebSocket server
        webSocketsServer.begin();                          // start the websocket server
        webSocketsServer.onEvent(
                webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
        Serial.println("WebSocket server started.");
    }

    static void checkTemperature() {
        double tempDifference = TempSensor::actualAndTargetTempDifference();

        if(tempDifference!=0){
            if(tempDifference>0)
                Actuator::open();
            else
                Actuator::close();
        }else
            Actuator::stop();

    }

}


#endif //NEWNODE_WEBSOCKETS_H
