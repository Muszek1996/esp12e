//
// Created by Jakub on 06.10.2018.
//
#include "config/Config.h"

namespace my{

    void managerPortalHttpService(const char *ApName, const char *password){
        WiFiManager wifiManager;
        wifiManager.autoConnect(ApName,password);
    }


}