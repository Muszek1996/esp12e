//
// Created by Jakub on 06.10.2018.
//
#include "helperFunctions/config/Config.h"
#include "Components/HTTP/Http.h"
#include "Components/WebSocket/WebSocket.h"
#include "Components/MyTaskScheduler/MyTaskScheduler.h"
#include "TaskScheduler.h"

void loop(){
    MyTaskScheduler::getInstance()->execute();
}