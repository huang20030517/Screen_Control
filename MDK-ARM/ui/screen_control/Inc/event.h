#ifndef __EVENT_H
#define __EVENT_H

#include "key.h"
#include "state.h"

// 事件处理函数声明
void Event_Task(void);
void Update_Selection(void);
void Event_Set_Interface_State(MenuState state);
void Event_Set_Value_Params(int current, int min, int max, int step);

#endif 