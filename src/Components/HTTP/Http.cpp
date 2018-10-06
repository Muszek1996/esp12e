//
// Created by Jakub on 08.08.2018.
//
#include "Http.h"
#include "config.h"


Http * Http::instance = nullptr;
ESP8266WebServer * Http::server;

Http *Http::getInstance() {
    if(Http::instance == nullptr){
        Http::instance = new Http();
    }
    return Http::instance;
}

void Http::execute() {
   server->handleClient();
}





Http::Http() {
   Http::server = new ESP8266WebServer(80);
    SPIFFS.begin();                           // Start the SPI Flash Files System
    server->begin();


    server->onNotFound([]() {                              // If the client requests any URI
        if (!handleFileRead(server->uri()))                  // send it if it exists
            server->send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
    });

}



String Http::getContentType(String filename) {// convert the file extension to the MIME type
    if(filename.endsWith(".htm")) return "text/html";
    else if(filename.endsWith(".html")) return "text/html";
    else if(filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "application/javascript";
    else if(filename.endsWith(".png")) return "image/png";
    else if(filename.endsWith(".gif")) return "image/gif";
    else if(filename.endsWith(".jpg")) return "image/jpeg";
    else if(filename.endsWith(".ico")) return "image/x-icon";
    else if(filename.endsWith(".xml")) return "text/xml";
    else if(filename.endsWith(".pdf")) return "application/x-pdf";
    else if(filename.endsWith(".zip")) return "application/x-zip";
    else if(filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

bool Http::handleFileRead(String path) { // send the right file to the client (if it exists)

    Serial.println("handleFileRead: " + path);
    if(path.endsWith("/")) path += "index.html";           // If a folder is requested, send the index file
    String contentType = getContentType(path);             // Get the MIME type
    String pathWithGz = path + ".gz";
    if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){  // If the file exists, either as a compressed archive, or normal
        if(SPIFFS.exists(pathWithGz))                          // If there's a compressed version available
            path += ".gz";                                         // Use the compressed version
        File file = SPIFFS.open(path, "r");                    // Open the file
        server->streamFile(file, contentType);    // Send it to the client
        file.close();                                          // Close the file again
        Serial.println(String("\tSent file: ") + path);
        return true;
    }
    Serial.println(String("\tFile Not Found: ") + path);
    return false;                                          // If the file doesn't exist, return false
}
