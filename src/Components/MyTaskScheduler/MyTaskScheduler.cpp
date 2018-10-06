//
// Created by Jakub on 07.08.2018.
//

#include "MyTaskScheduler.h"

MyTaskScheduler * MyTaskScheduler::instance = nullptr;

MyTaskScheduler *MyTaskScheduler::getInstance() {
    if(MyTaskScheduler::instance == nullptr){
        MyTaskScheduler::instance = new MyTaskScheduler();
    }
    return MyTaskScheduler::instance;
}

Task *MyTaskScheduler::getTasks() {
    return *tasks;
}

