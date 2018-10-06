//
// Created by Jakub on 07.08.2018.
//

#ifndef NODEMCU_MYTASKSCHEDULER_H
#define NODEMCU_MYTASKSCHEDULER_H
#include "TaskSchedulerDeclarations.h"

class MyTaskScheduler : public Scheduler {
   static MyTaskScheduler * instance;
   static Task *tasks[4];
public:
   static MyTaskScheduler* getInstance();
    static Task *getTasks();
};


#endif //NODEMCU_MYTASKSCHEDULER_H
