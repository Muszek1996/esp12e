//
// Created by Jakub on 06.10.2018.
//

#ifndef ESP12E_TEMPSENSOR_H
#define ESP12E_TEMPSENSOR_H

#include <cstdint>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>



class TempSensor {
public:
    static const int tempBias;
    static const uint8_t iCsQuantity;
    static double *lastTemps;
    static double getTargetTemp();
    static void setTargetTemp(double targetTemp);
    static double targetTemp;
    static const double tolerance;

    static const uint8_t getICsQuantity();

    static double *getLastTemps();

    static double actualAndTargetTempDifference(){   // zwraca nadwyżkę temperatury+/niedobór-;
        double averageTemp = getAverageTemp();
        if(averageTemp>(targetTemp+tolerance)||averageTemp<(targetTemp-tolerance))return ((targetTemp+tolerance)-averageTemp);
        else return 0;
    }

    static void begin(){
        sensors.begin();
    }

    static OneWire oneWire;
    static DallasTemperature sensors;



    static void getTemps(){
        sensors.requestTemperatures();
        for(uint8_t i=0;i<iCsQuantity;++i){
            lastTemps[i]=(sensors.getTempCByIndex(iCsQuantity-1-i)+tempBias);
        }
    }

    static double getAverageTemp(){
        getTemps();
        double temp=0;
        for(int i=0;i<iCsQuantity;i++){
            temp+=lastTemps[i];
        }
        temp/=iCsQuantity;
        return temp;
    }

    static double getMyTempCByIndex(uint8_t i){
        if(i<0||i>iCsQuantity) return -126.6969;
        sensors.requestTemperatures();
        lastTemps[i]=(sensors.getTempCByIndex(iCsQuantity-1-i)+tempBias);
        return lastTemps[i];
    }

    static String getStringTemp(uint8_t i){
        double temp = getMyTempCByIndex(i);
        String tempStr = String(temp);
        return tempStr;
    }




};


#endif //ESP12E_TEMPSENSOR_H
