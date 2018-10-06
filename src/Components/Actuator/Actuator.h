//
// Created by Jakub on 06.10.2018.
//

#ifndef ESP12E_ACTUATOR_H
#define ESP12E_ACTUATOR_H


#include <Arduino.h>

class Actuator {
private:
    static int speed;
    static const uint8_t Pin1;
    static const uint8_t Pin2;
public:
    static int getSpeed();

public:
    Actuator(const int Pin1, const int Pin2);
    static void open();
    static void close();
    static void stop();

    static void setSpeed(int speed);
};


#endif //ESP12E_ACTUATOR_H
