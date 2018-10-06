//
// Created by Jakub on 08.08.2018.
//

#ifndef NODEMCU_HTTP_H
#define NODEMCU_HTTP_H


#include <ESP8266WebServer.h>
#include <FS.h>   // Include the SPIFFS library


class Http {
    Http();
    static Http * instance;
    static void handleRoot();
    static void handleNotFound();
    static void drawGraph();
    static String getContentType(String filename);
    static bool handleFileRead(String path);
public:
    static void execute();
    static ESP8266WebServer *server;
    static Http *getInstance();
};


#endif //NODEMCU_HTTP_H
