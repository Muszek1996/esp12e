//
// Created by Jakub on 06.10.2018.
//

#include "TempSensor.h"
#include "../WebSocket/WebSocket.h"

const int TempSensor::tempBias = -2;
const uint8_t TempSensor::iCsQuantity = 2;
double *TempSensor::lastTemps = new double[2];
double TempSensor::targetTemp = 21;
OneWire TempSensor::oneWire(D3);
DallasTemperature TempSensor::sensors(&oneWire);
const double TempSensor::tolerance = 0.25;

double TempSensor::getTargetTemp() {
    return TempSensor::targetTemp;
}

void TempSensor::setTargetTemp(double targetTemp) {
    TempSensor::targetTemp = targetTemp;
}

double *TempSensor::getLastTemps() {
    return TempSensor::lastTemps;
}

const uint8_t TempSensor::getICsQuantity() {
    return TempSensor::iCsQuantity;
}
