#ifndef __UI_H
#define __UI_H

#include "key.h"
#include "state.h"  
#include "data.h"
#include "TJC4832K035_011N.h"
#include "menu_draw.h"
#include "stdbool.h"


/**
 * @brief 界面状态结构体
 */
typedef struct {
    void (*draw)(void);                    // 界面绘制函数
    void (*on_key)(KeyEvent key_event);    // 按键处理函数
    const char* title;                     // 界面标题
    const char** menu_items;               // 菜单项
    int item_count;                        // 菜单项数量
} UIState;

void UI_Init(void);
void UI_Task(void);

#endif

