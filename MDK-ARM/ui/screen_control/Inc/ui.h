#ifndef __UI_H
#define __UI_H

#include "key.h"

// UI 绘制函数
void UI_Init(void);
void UI_Task(void);
void Draw_Menu(void);
void Draw_Work_Params_Menu(void);
void Draw_Work_Mode_Menu(void);
void Draw_Controller_Menu(void);

// 选择管理函数
int Get_Current_Selection(void);
void Set_Current_Selection(int selection);

// 按键处理桥接函数
void UI_Handle_Enter_Key(void);
void UI_Handle_Back_Key(void);

#endif 