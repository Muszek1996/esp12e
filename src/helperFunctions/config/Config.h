//
// Created by Jakub on 06.10.2018.
//

#ifndef ESP12E_CONFIG_H
#define ESP12E_CONFIG_H
#include <Arduino.h>
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


class Config {
    const char* ssid;
    const char* password;
    const int espPort;
    const char* hostname;
    const char* espPassword ;
public:
    String toString();
    Config(const char* ssid, const char* password, const int espPort, const char* hostname, const char* espPassword);

    const char *getSsid() const;

    const char *getPassword() const;

    const int getEspPort() const;

    const char *getHostname() const;

    const char *getEspPassword() const;
};


#endif //ESP12E_CONFIG_H
