//
// Created by Jakub on 06.10.2018.
//

#include "Config.h"

Config::Config(const char* ssid, const char* password, const int espPort, const char* hostname, const char* espPassword):
ssid(ssid),
password(password),
espPort(espPort),
hostname(hostname),
espPassword(espPassword) {

}

String Config::toString() {
    String configParameters = "SSID:";
    configParameters+=ssid;
    configParameters+="\n";
    configParameters+="AP-PASSWORD:";
    configParameters+=password;
configParameters+="\n";
    configParameters+="ESP-PORT:";
    configParameters+=espPort;
    configParameters+="\n";
    configParameters+="ESP-PASSWORD:";
    configParameters+=espPassword;
configParameters+="\n";
    configParameters+="HOSTNAME:";
    configParameters+=hostname;

    return configParameters;
}

const char *Config::getSsid() const {
    return ssid;
}
const char *Config::getPassword() const {
    return password;
}
const int Config::getEspPort() const {
    return espPort;
}
const char *Config::getHostname() const {
    return hostname;
}
const char *Config::getEspPassword() const {
    return espPassword;
}

