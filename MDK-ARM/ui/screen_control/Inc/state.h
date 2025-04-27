#ifndef __STATE_H
#define __STATE_H

#include <stdbool.h>
#include "key.h"
#include "TJC4832K035_011N.h"

/**
 * @brief 菜单状态枚举
 */
typedef enum
{
    STATE_MAIN_MENU = 0, // 主菜单状态
    STATE_WORK_PARAMS,   // 工作参数设置状态
    STATE_WORK_MODE,     // 工作模式选择状态
    STATE_CONTROLLER,    // 控制器参数设置状态
    STATE_COUNT          // 状态总数
} MenuState;

/**
 * @brief 数据操作类型枚举
 */
typedef enum {
    DATA_OP_READ,          // 读取数据
    DATA_OP_WRITE,         // 写入数据
    DATA_OP_UPDATE         // 更新显示
} DataOperation;

/**
 * @brief 界面数据结构
 */
typedef struct {
    int current_value;     // 当前值
    int min_value;         // 最小值
    int max_value;         // 最大值
    int step_value;        // 步进值
    bool is_modified;      // 是否被修改
} UIData;

/**
 * @brief 界面状态结构体
 */
typedef struct {
    void (*draw)(void);                    // 界面绘制函数
    void (*on_key)(KeyEvent key_event);    // 按键处理函数
    void (*on_data)(DataOperation op, UIData* data);  // 数据处理函数
    const char* title;                     // 界面标题
    const char** menu_items;               // 菜单项
    int item_count;                        // 菜单项数量
} UIState;

// 状态管理函数声明
void State_Init(void);                         // 初始化状态管理模块
MenuState State_Get_Current(void);             // 获取当前状态
void State_Change(MenuState new_state);        // 切换到新状态
void State_Handle_Back(void);                  // 处理返回操作
void State_Process_Key(KeyEvent key_event);    // 处理按键事件

// 界面任务函数
void State_Task(void);                         // 状态管理主任务函数

// 数据操作函数
void State_Read_Data(MenuState state, UIData* data);   // 读取数据
void State_Write_Data(MenuState state, UIData* data);  // 写入数据
void State_Update_Display(MenuState state);            // 更新显示

// UI接口函数前置声明
int GetCurrentSelection(void);
void SetCurrentSelection(int selection);

#endif 