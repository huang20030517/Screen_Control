#include "ui.h"
#include <string.h>
#include <stdio.h>
#include "TJC4832K035_011N.h"
#include "event.h"
#include "state.h"

// 屏幕基础参数
#define SCREEN_WIDTH 480  // 屏幕宽度
#define SCREEN_HEIGHT 320 // 屏幕高度

// 当前选中的菜单项
int current_selection = 0;
int previous_selection = -1; // 记录上一次选择位置，便于擦除旧箭头

// 菜单项位置
int menu_y[] = {100, 150, 200};

// 菜单项文本
const char *menu_items[] = {
    "\"工作参数设置\"",
    "\"工作模式选择\"",
    "\"控制器参数设置\""
};

// 工作参数设置菜单项
const char *work_params_items[] = {
    "\"速度设置\"",
    "\"温度设置\"",
    "\"时间设置\"",
    "\"保存退出\""
};

// 工作模式选择菜单项
const char *work_mode_items[] = {
    "\"标准模式\"",
    "\"高级模式\"",
    "\"自动模式\"",
    "\"手动模式\""
};

// 控制器参数菜单项
const char *controller_items[] = {
    "\"PID参数\"",
    "\"通信设置\"",
    "\"系统校准\"",
    "\"返回主菜单\""
};

// 子菜单按键处理函数前置声明
static void WorkParamsKeyHandler(KeyID key_id, KeyEventType event_type);
static void WorkModeKeyHandler(KeyID key_id, KeyEventType event_type);
static void ControllerKeyHandler(KeyID key_id, KeyEventType event_type);

// 初始化UI
void UI_Init(void)
{
    // 初始化按键
    Key_Init();
    
    // 初始化状态管理
    State_Init();
    
    // 初始化屏幕
    Set_Screen_Sleep(0);
    Screen_Clear(LIGHT_BLUE);
    
    // 初始显示菜单
    Draw_Menu();
}

// 绘制主菜单
void Draw_Menu(void) 
{
    // 清除屏幕以便重新绘制
    Screen_Clear(LIGHT_BLUE);
    
    // 主标题
    Send_Xstr(190, 30, 200, 40, 3, BLACK, LIGHT_BLUE, 0, 1, 3, "\"主菜单\"");

    // 显示菜单项
    Send_Xstr(150, menu_y[0], 250, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, (char *)menu_items[0]);
    Send_Xstr(150, menu_y[1], 250, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, (char *)menu_items[1]);
    Send_Xstr(150, menu_y[2], 250, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, (char *)menu_items[2]);

    // 为当前选中项显示箭头
    Send_Xstr(110, menu_y[current_selection], 35, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, "\"->\"");

    // 底部提示
    Send_Xstr(110, 280, 280, 35, 1, YELLOW, LIGHT_BLUE, 0, 1, 3, "\"↑↓选择   FOR进入   BACK返回\"");

    // 记录当前选择
    previous_selection = current_selection;
}

// 绘制工作参数设置菜单
void DrawWorkParamsMenu(void) 
{
    // 清除屏幕以便重新绘制
    Screen_Clear(LIGHT_BLUE);
    
    // 菜单标题
    Send_Xstr(150, 30, 250, 40, 3, BLACK, LIGHT_BLUE, 0, 1, 3, "\"工作参数设置\"");

    // 显示菜单项
    for (int i = 0; i < 4; i++) {
        uint16_t text_color = (i == current_selection) ? RED : BLACK;
        Send_Xstr(150, menu_y[0] + i * 40, 250, 35, 2, text_color, LIGHT_BLUE, 0, 1, 3, (char *)work_params_items[i]);
        
        if (i == current_selection) {
            Send_Xstr(110, menu_y[0] + i * 40, 35, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, "\"→\"");
        }
    }

    // 底部提示
    Send_Xstr(110, 280, 280, 35, 1, YELLOW, LIGHT_BLUE, 0, 1, 3, "\"↑↓选择   FOR确认   BACK返回\"");

    // 记录当前选择
    previous_selection = current_selection;
    
    // 注册工作参数菜单的按键处理函数
    Event_RegisterKeyHandler(WorkParamsKeyHandler);
}

// 绘制工作模式选择菜单
void DrawWorkModeMenu(void) 
{
    // 清除屏幕以便重新绘制
    Screen_Clear(LIGHT_BLUE);
    
    // 菜单标题
    Send_Xstr(150, 30, 250, 40, 3, BLACK, LIGHT_BLUE, 0, 1, 3, "\"工作模式选择\"");

    // 显示菜单项
    for (int i = 0; i < 4; i++) {
        uint16_t text_color = (i == current_selection) ? RED : BLACK;
        Send_Xstr(150, menu_y[0] + i * 40, 250, 35, 2, text_color, LIGHT_BLUE, 0, 1, 3, (char *)work_mode_items[i]);
        
        if (i == current_selection) {
            Send_Xstr(110, menu_y[0] + i * 40, 35, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, "\"→\"");
        }
    }

    // 底部提示
    Send_Xstr(110, 280, 280, 35, 1, YELLOW, LIGHT_BLUE, 0, 1, 3, "\"↑↓选择   FOR确认   BACK返回\"");

    // 记录当前选择
    previous_selection = current_selection;
    
    // 注册工作模式菜单的按键处理函数
    Event_RegisterKeyHandler(WorkModeKeyHandler);
}

// 绘制控制器参数设置菜单
void DrawControllerMenu(void) 
{
    // 清除屏幕以便重新绘制
    Screen_Clear(LIGHT_BLUE);
    
    // 菜单标题
    Send_Xstr(150, 30, 250, 40, 3, BLACK, LIGHT_BLUE, 0, 1, 3, "\"控制器参数设置\"");

    // 显示菜单项
    for (int i = 0; i < 4; i++) {
        uint16_t text_color = (i == current_selection) ? RED : BLACK;
        Send_Xstr(150, menu_y[0] + i * 40, 250, 35, 2, text_color, LIGHT_BLUE, 0, 1, 3, (char *)controller_items[i]);
        
        if (i == current_selection) {
            Send_Xstr(110, menu_y[0] + i * 40, 35, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, "\"→\"");
        }
    }

    // 底部提示
    Send_Xstr(110, 280, 280, 35, 1, YELLOW, LIGHT_BLUE, 0, 1, 3, "\"↑↓选择   FOR确认   BACK返回\"");

    // 记录当前选择
    previous_selection = current_selection;
    
    // 注册控制器参数菜单的按键处理函数
    Event_RegisterKeyHandler(ControllerKeyHandler);
}

// 主UI任务，处理按键和界面更新
void UI_Task(void)
{
    // 调用事件处理任务
    Event_Task();
    
    HAL_Delay(10);
}

// 获取当前选择
int Get_Current_Selection(void)
{
    return current_selection;
}

// 设置当前选择
void Set_Current_Selection(int selection)
{
    if (selection >= 0 && selection < 3)  // 确保选择在有效范围内
    {
        current_selection = selection;
    }
}

// 处理ENTER键的桥接函数
void UI_Handle_Enter_Key(void)
{
    // 根据当前选中项导航到相应子菜单
    State_Handle_MainMenu_Selection(current_selection);
}

// 处理BACK键的桥接函数
void UI_Handle_Back_Key(void)
{
    // 处理返回操作
    State_Handle_Back();
}

// 工作参数菜单按键处理
static void WorkParamsKeyHandler(KeyID key_id, KeyEventType event_type)
{
    if (event_type == KEY_EVENT_SHORT_PRESS)
    {
        switch (key_id)
        {
            case KEY_ID_UP:
                // 向上选择
                if (current_selection > 0)
                {
                    current_selection--;
                    // 这里需要更新工作参数菜单的选择
                    DrawWorkParamsMenu();
                }
                break;
            
            case KEY_ID_DOWN:
                // 向下选择
                if (current_selection < 3) // 4个菜单项
                { 
                    current_selection++;
                    DrawWorkParamsMenu();
                }
                break;
            
            case KEY_ID_FOR:
                // 根据选择执行操作
                if (current_selection == 3) // 保存退出
                {
                    // 返回主菜单
                    State_Handle_Back();
                }
                else
                {
                    // 其他选项的操作
                    // 可以显示相应的设置界面
                }
                break;
            
            case KEY_ID_BACK:
                // 返回主菜单
                State_Handle_Back();
                break;
                
            default:
                break;
        }
    }
}

// 工作模式菜单按键处理
static void WorkModeKeyHandler(KeyID key_id, KeyEventType event_type)
{
    if (event_type == KEY_EVENT_SHORT_PRESS)
    {
        switch (key_id)
        {
            case KEY_ID_UP:
                // 向上选择
                if (current_selection > 0)
                {
                    current_selection--;
                    DrawWorkModeMenu();
                }
                break;
            
            case KEY_ID_DOWN:
                // 向下选择
                if (current_selection < 3) // 4个菜单项
                { 
                    current_selection++;
                    DrawWorkModeMenu();
                }
                break;
            
            case KEY_ID_FOR:
                // 选择工作模式
                // 可以显示确认信息
                {
                    // 显示选择确认信息
                    char message[50];
                    sprintf(message, "\"已选择: %s\"", work_mode_items[current_selection] + 1); // +1跳过第一个引号
                    
                    // 清屏显示消息
                    Screen_Clear(LIGHT_BLUE);
                    Send_Xstr(120, 150, 240, 40, 2, BLACK, LIGHT_BLUE, 0, 1, 3, message);
                    
                    // 延时后返回主菜单
                    HAL_Delay(1000);
                    State_Handle_Back();
                }
                break;
            
            case KEY_ID_BACK:
                // 返回主菜单
                State_Handle_Back();
                break;
                
            default:
                break;
        }
    }
}

// 控制器参数菜单按键处理
static void ControllerKeyHandler(KeyID key_id, KeyEventType event_type)
{
    if (event_type == KEY_EVENT_SHORT_PRESS)
    {
        switch (key_id)
        {
            case KEY_ID_UP:
                // 向上选择
                if (current_selection > 0)
                {
                    current_selection--;
                    DrawControllerMenu();
                }
                break;
            
            case KEY_ID_DOWN:
                // 向下选择
                if (current_selection < 3) // 4个菜单项
                { 
                    current_selection++;
                    DrawControllerMenu();
                }
                break;
            
            case KEY_ID_FOR:
                // 处理选择
                if (current_selection == 3) // 返回主菜单
                {
                    State_Handle_Back();
                }
                else
                {
                    // 其他选项的操作
                    // 可以显示相应的设置界面
                }
                break;
            
            case KEY_ID_BACK:
                // 返回主菜单
                State_Handle_Back();
                break;
                
            default:
                break;
        }
    }
}