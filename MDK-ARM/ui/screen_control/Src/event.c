/**
 * @file event.c
 * @brief 事件处理模块，负责处理按键事件和界面更新
 */

#include "event.h"
#include "ui.h"
#include "key.h"
#include "TJC4832K035_011N.h"
#include "state.h"

// 声明外部变量
extern int current_selection;    // 当前选中的菜单项
extern int previous_selection;   // 上一次选中的菜单项
extern int menu_y[];            // 菜单项的Y坐标数组
extern const char* menu_items[]; // 菜单项文本数组

// 声明UI处理函数
extern void UI_Handle_Enter_Key(void);
extern void UI_Handle_Back_Key(void);

// 声明当前界面状态
static MenuState current_interface_state = STATE_MAIN_MENU;

// 声明数据编辑状态
static bool is_editing_value = false;
static int current_value = 0;
static int min_value = 0;
static int max_value = 100;
static int step_value = 1;

/**
 * @brief 更新菜单选中状态
 * @details 当菜单选择发生变化时，更新界面显示
 */
void Update_Selection(void)
{
    // 如果选择已改变
    if (current_selection != previous_selection)
    {
        // 清除旧箭头
        Send_Xstr(110, menu_y[previous_selection], 35, 35, 2, LIGHT_BLUE, LIGHT_BLUE, 0, 1, 1, "\"   \"");
        
        // 刷新显示当前选中项
        Send_Xstr(150, menu_y[current_selection], 250, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, (char *)menu_items[current_selection]);
        
        // 绘制新箭头
        Send_Xstr(110, menu_y[current_selection], 35, 35, 2, BLACK, LIGHT_BLUE, 0, 1, 3, "\"->\"");
        
        // 记录当前选择
        previous_selection = current_selection;
    }
}

/**
 * @brief 更新数值显示
 * @details 当数值改变时更新显示
 */
void Update_Value_Display(void)
{
    char value_str[32];
    sprintf(value_str, "\"%d\"", current_value);
    // 在适当位置显示数值
    Send_Xstr(200, menu_y[current_selection], 100, 35, 2, RED, LIGHT_BLUE, 0, 1, 3, value_str);
}

/**
 * @brief 处理主菜单按键
 */
static void Handle_Main_Menu_Keys(KeyEvent key_event)
{
    switch (key_event.key_id)
    {
        case KEY_ID_UP:
            if (current_selection > 0)
            {
                current_selection--;
                Update_Selection();
            }
            break;
        
        case KEY_ID_DOWN:
            if (current_selection < 2)
            { 
                current_selection++;
                Update_Selection();
            }
            break;
        
        case KEY_ID_FOR:
        case KEY_ID_ENTER:
            UI_Handle_Enter_Key();
            break;
        
        case KEY_ID_BACK:
            UI_Handle_Back_Key();
            break;

        case KEY_ID_START:  // 开始按键在主菜单中不处理
        case KEY_ID_STOP:   // 停止按键在主菜单中不处理
        case KEY_ID_SELECT: // 选择按键在主菜单中不处理
        case KEY_ID_REMOTE: // 远程控制在主菜单中不处理
            break;
            
        default:
            break;
    }
}

/**
 * @brief 处理参数设置界面按键
 */
static void Handle_Param_Setting_Keys(KeyEvent key_event)
{
    if (!is_editing_value)
    {
        // 未在编辑状态，SELECT键用于选择参数
        switch (key_event.key_id)
        {
            case KEY_ID_SELECT:
                if (current_selection > 0)
                {
                    current_selection--;
                    Update_Selection();
                }
                break;
            
            case KEY_ID_ENTER:
                if (current_selection < 2)
                { 
                    current_selection++;
                    Update_Selection();
                }
                break;
            
            case KEY_ID_FOR:
                // 进入编辑状态
                is_editing_value = true;
                break;
            
            case KEY_ID_BACK:
                UI_Handle_Back_Key();
                break;

            case KEY_ID_START:  // 开始按键在参数设置中不处理
            case KEY_ID_STOP:   // 停止按键在参数设置中不处理
            case KEY_ID_UP:     // 上键在非编辑状态下不处理
            case KEY_ID_DOWN:   // 下键在非编辑状态下不处理
            case KEY_ID_REMOTE: // 远程控制在参数设置中不处理
                break;
                
            default:
                break;
        }
    }
    else
    {
        // 在编辑状态，UP/DOWN用于调整数值
        switch (key_event.key_id)
        {
            case KEY_ID_UP:
                if (current_value < max_value)
                {
                    current_value += step_value;
                    Update_Value_Display();
                }
                break;
            
            case KEY_ID_DOWN:
                if (current_value > min_value)
                {
                    current_value -= step_value;
                    Update_Value_Display();
                }
                break;
            
            case KEY_ID_FOR:
                // 退出编辑状态并保存
                is_editing_value = false;
                break;
            
            case KEY_ID_BACK:
                // 取消编辑
                is_editing_value = false;
                break;

            case KEY_ID_START:  // 开始按键在编辑状态下不处理
            case KEY_ID_STOP:   // 停止按键在编辑状态下不处理
            case KEY_ID_SELECT: // 选择按键在编辑状态下不处理
            case KEY_ID_ENTER:  // 确认按键在编辑状态下不处理
            case KEY_ID_REMOTE: // 远程控制在编辑状态下不处理
                break;
                
            default:
                break;
        }
    }
}

/**
 * @brief 事件任务处理函数
 * @details 主要处理按键事件，根据不同界面状态执行相应操作
 */
void Event_Task(void)
{
    // 获取按键事件
    KeyEvent key_event = Key_Scan();
    
    // 处理有效按键事件
    if (key_event.event_type != KEY_EVENT_UNKNOWN)
    {
        // 处理短按事件
        if (key_event.event_type == KEY_EVENT_SHORT_PRESS)
        {
            // 根据当前界面状态处理按键
            switch (current_interface_state)
            {
                case STATE_MAIN_MENU:
                    Handle_Main_Menu_Keys(key_event);
                    break;
                
                case STATE_WORK_PARAMS:
                case STATE_CONTROLLER:
                    Handle_Param_Setting_Keys(key_event);
                    break;
                
                case STATE_WORK_MODE:
                    Handle_Main_Menu_Keys(key_event); // 工作模式选择使用与主菜单相同的按键处理
                    break;
                
                default:
                    break;
            }
        }
        // 处理长按事件
        else if (key_event.event_type == KEY_EVENT_LONG_PRESS)
        {
            if (is_editing_value)
            {
                // 在编辑状态下的长按处理
                switch (key_event.key_id)
                {
                    case KEY_ID_UP:
                        // 快速增加值
                        current_value = min(current_value + step_value * 10, max_value);
                        Update_Value_Display();
                        break;
                    
                    case KEY_ID_DOWN:
                        // 快速减少值
                        current_value = max(current_value - step_value * 10, min_value);
                        Update_Value_Display();
                        break;
                }
            }
            else
            {
                // 非编辑状态下的长按处理
                switch (key_event.key_id)
                {
                    case KEY_ID_UP:
                        current_selection = 0;
                        Update_Selection();
                        break;
                    
                    case KEY_ID_DOWN:
                        current_selection = 2;
                        Update_Selection();
                        break;
                }
            }
        }
    }
}

/**
 * @brief 设置界面状态
 * @param state 新的界面状态
 */
void Event_Set_Interface_State(MenuState state)
{
    current_interface_state = state;
    is_editing_value = false; // 切换界面时退出编辑状态
}

/**
 * @brief 设置数值编辑参数
 */
void Event_Set_Value_Params(int current, int min, int max, int step)
{
    current_value = current;
    min_value = min;
    max_value = max;
    step_value = step;
}