//
// Created by Jakub on 06.10.2018.
//

#include "Actuator.h"
#include "../WebSocket/WebSocket.h"

int Actuator::speed = 300;
const uint8_t Actuator::Pin1 = D1;
const uint8_t Actuator::Pin2 = D2;


void Actuator::setSpeed(int speed) {
        Actuator::speed = speed;
}

void Actuator::open() {
        analogWrite(Pin1,0);
        analogWrite(Pin2,speed);
}

void Actuator::close() {
        analogWrite(Pin1,speed);
        analogWrite(Pin2,0);
}

void Actuator::stop() {
        digitalWrite(Pin1,0);
        digitalWrite(Pin2,0);
}

int Actuator::getSpeed() {
        return speed;
}
