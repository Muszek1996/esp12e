//
// Created by Jakub on 06.10.2018.
//

#include <TaskSchedulerDeclarations.h>
#include "helperFunctions/config/Config.h"
#include "helperFunctions/myFunc.h"
#include "Components/Actuator/Actuator.h"
#include "Components/TempSensor/TempSensor.h"
#include "Components/WebSocket/WebSocket.h"
#include "Components/HTTP/Http.h"
#include "Components/MyTaskScheduler/MyTaskScheduler.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


Task HTTP(50,TASK_FOREVER, Http::execute, MyTaskScheduler::getInstance(),true);
Task Temp(60*TASK_SECOND,TASK_FOREVER, WebSocket::getTemps,MyTaskScheduler::getInstance(),true);
Task WebSocketHandler(33,TASK_FOREVER, WebSocket::webSocketLoop,MyTaskScheduler::getInstance(),true);
Task WebSocketTemperatureReporter(1*TASK_SECOND,TASK_FOREVER, WebSocket::reportTemperatures,MyTaskScheduler::getInstance(),true);
Task TempControll(5*TASK_SECOND,TASK_FOREVER, WebSocket::checkTemperature,MyTaskScheduler::getInstance(),true);

const char *ssid = "ESPap";
const char *password = "K0nr4f4l";


auto *cfg = new Config("401A","K0nr4f4l",8266,"okno","K0nr4f4l");
void setup(){
    delay(3000);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);


    Http::getInstance();



    WebSocket::startWebSocket();
    TempSensor::begin();

    Serial.println(cfg->toString());


}



