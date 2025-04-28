#ifndef __UI_H
#define __UI_H

#include "key.h"

// UI 任务函数
void UI_Init(void);
void UI_Task(void);

// 选择管理函数
int Get_Current_Selection(void);
void Set_Current_Selection(int selection);

// 按键处理桥接函数
void UI_Handle_Enter_Key(void);
void UI_Handle_Back_Key(void);

#endif 