/**
 * @file state.c
 * @brief 状态管理模块，负责处理界面状态切换和按键处理
 */

#include "state.h"
#include "key.h"
#include "TJC4832K035_011N.h"

// 菜单状态定义
typedef enum {
    STATE_MAIN_MENU = 0,    // 主菜单
    STATE_WORK_PARAMS,      // 工作参数设置
    STATE_WORK_MODE,        // 工作模式选择
    STATE_CONTROLLER,       // 控制器参数设置
    STATE_COUNT             // 状态总数
} MenuState;

// 当前菜单状态
static MenuState current_state = STATE_MAIN_MENU;

// 每个菜单的选择记忆
static int menu_selections[STATE_COUNT] = {0};

// 每个界面的数据
static UIData state_data[STATE_COUNT] = {0};

// 主菜单项
static const char* main_menu_items[] = {
    "\"工作参数设置\"",
    "\"工作模式选择\"",
    "\"控制器参数设置\""
};

// 工作参数菜单项
static const char* work_params_items[] = {
    "\"速度设置\"",
    "\"温度设置\"",
    "\"时间设置\"",
    "\"保存退出\""
};

// 工作模式菜单项
static const char* work_mode_items[] = {
    "\"标准模式\"",
    "\"高级模式\"",
    "\"自动模式\"",
    "\"手动模式\""
};

// 控制器参数菜单项
static const char* controller_items[] = {
    "\"PID参数\"",
    "\"通信设置\"",
    "\"系统校准\"",
    "\"返回主菜单\""
};

// 是否处于编辑状态
static bool is_editing = false;

// 前向声明界面处理函数
static void Draw_Main_Menu(void);
static void Draw_Work_Params(void);
static void Draw_Work_Mode(void);
static void Draw_Controller(void);

static void Handle_Main_Menu_Keys(KeyEvent key_event);
static void Handle_Work_Params_Keys(KeyEvent key_event);
static void Handle_Work_Mode_Keys(KeyEvent key_event);
static void Handle_Controller_Keys(KeyEvent key_event);

// 界面状态定义
static const UIState ui_states[STATE_COUNT] = {
    [STATE_MAIN_MENU] = {
        .draw = Draw_Main_Menu,
        .on_key = Handle_Main_Menu_Keys,
        .title = "\"主菜单\"",
        .menu_items = main_menu_items,
        .item_count = 3
    },
    [STATE_WORK_PARAMS] = {
        .draw = Draw_Work_Params,
        .on_key = Handle_Work_Params_Keys,
        .title = "\"工作参数设置\"",
        .menu_items = work_params_items,
        .item_count = 4
    },
    [STATE_WORK_MODE] = {
        .draw = Draw_Work_Mode,
        .on_key = Handle_Work_Mode_Keys,
        .title = "\"工作模式选择\"",
        .menu_items = work_mode_items,
        .item_count = 4
    },
    [STATE_CONTROLLER] = {
        .draw = Draw_Controller,
        .on_key = Handle_Controller_Keys,
        .title = "\"控制器参数设置\"",
        .menu_items = controller_items,
        .item_count = 4
    }
};

/**
 * @brief 初始化状态管理模块
 */
void State_Init(void)
{
    // 初始化按键
    Key_Init();
    
    // 初始化LCD
    Screen_Clear(BLACK);
    
    // 初始化状态
    current_state = STATE_MAIN_MENU;
    for (int i = 0; i < STATE_COUNT; i++) {
        menu_selections[i] = 0;
    }
    
    // 绘制初始界面
    ui_states[current_state].draw();
}

/**
 * @brief 获取当前状态
 */
MenuState State_Get_Current(void)
{
    return current_state;
}

/**
 * @brief 切换到新状态
 */
void State_Change(MenuState new_state)
{
    if (new_state < STATE_COUNT) {
        current_state = new_state;
        ui_states[current_state].draw();
    }
}

/**
 * @brief 处理返回操作
 */
void State_Handle_Back(void)
{
    if (is_editing) {
        // 如果在编辑状态，退出编辑状态
        is_editing = false;
        ui_states[current_state].draw();
    } else if (current_state != STATE_MAIN_MENU) {
        // 如果不在主菜单，返回主菜单
        State_Change(STATE_MAIN_MENU);
    }
}

/**
 * @brief 处理按键事件
 */
void State_Process_Key(KeyEvent key_event)
{
    // 如果有有效按键事件
    if (key_event.event_type != KEY_EVENT_UNKNOWN) {
        // 将按键传递给当前状态的处理函数
        if (ui_states[current_state].on_key != NULL) {
            ui_states[current_state].on_key(key_event);
        }
    }
}

/**
 * @brief 状态管理主任务函数
 */
void State_Task(void)
{
    // 获取按键事件
    KeyEvent key_event = Key_Scan();
    
    // 处理按键
    State_Process_Key(key_event);
    
    // 其他任务处理...
    HAL_Delay(10);
}

/*** 下面是各个界面的实现 ***/

/**
 * @brief 绘制主菜单
 */
static void Draw_Main_Menu(void)
{
    // 清屏
    Screen_Clear(BLACK);
    
    // 绘制标题
    int title_x = 190;
    int title_y = 30;
    Send_Xstr(title_x, title_y, 200, 40, 3, BLUE, BLACK, 1, 1, 3, (char*)ui_states[STATE_MAIN_MENU].title);
    
    // 绘制菜单项
    int item_x = 150;
    int start_y = 100;
    int item_height = 50;
    int current_selection = menu_selections[STATE_MAIN_MENU];
    
    for (int i = 0; i < ui_states[STATE_MAIN_MENU].item_count; i++) {
        int y = start_y + i * item_height;
        
        if (i == current_selection) {
            // 选中项显示箭头和高亮
            Send_Xstr(110, y, 35, 35, 2, RED, BLACK, 0, 1, 3, "\"->\"");
            Send_Xstr(item_x, y, 250, 35, 2, RED, BLACK, 0, 1, 3, (char*)ui_states[STATE_MAIN_MENU].menu_items[i]);
        } else {
            Send_Xstr(item_x, y, 250, 35, 2, WHITE, BLACK, 0, 1, 3, (char*)ui_states[STATE_MAIN_MENU].menu_items[i]);
        }
    }
    
    // 绘制底部提示
    Send_Xstr(120, 280, 280, 35, 1, YELLOW, BLACK, 0, 1, 3, "\"[↑↓]选择 [确认]进入 [返回]退出\"");
}

/**
 * @brief 绘制工作参数菜单
 */
static void Draw_Work_Params(void)
{
    Screen_Clear(BLACK);
    
    // 绘制标题
    int title_x = 190;
    int title_y = 30;
    Send_Xstr(title_x, title_y, 200, 40, 3, BLUE, BLACK, 1, 1, 3, (char*)ui_states[STATE_WORK_PARAMS].title);
    
    // 绘制菜单项
    int item_x = 150;
    int start_y = 100;
    int item_height = 50;
    int current_selection = menu_selections[STATE_WORK_PARAMS];
    
    for (int i = 0; i < ui_states[STATE_WORK_PARAMS].item_count; i++) {
        int y = start_y + i * item_height;
        
        if (i == current_selection) {
            // 选中项显示箭头和高亮
            Send_Xstr(110, y, 35, 35, 2, RED, BLACK, 0, 1, 3, "\"->\"");
            Send_Xstr(item_x, y, 250, 35, 2, RED, BLACK, 0, 1, 3, (char*)ui_states[STATE_WORK_PARAMS].menu_items[i]);
        } else {
            Send_Xstr(item_x, y, 250, 35, 2, WHITE, BLACK, 0, 1, 3, (char*)ui_states[STATE_WORK_PARAMS].menu_items[i]);
        }
    }
    
    // 绘制底部提示
    if (is_editing) {
        Send_Xstr(120, 280, 280, 35, 1, YELLOW, BLACK, 0, 1, 3, "\"[↑↓]调整 [确认]完成 [返回]取消\"");
    } else {
        Send_Xstr(120, 280, 280, 35, 1, YELLOW, BLACK, 0, 1, 3, "\"[↑↓]选择 [确认]编辑 [返回]退出\"");
    }
}

/**
 * @brief 绘制工作模式菜单
 */
static void Draw_Work_Mode(void)
{
    Screen_Clear(BLACK);
    
    // 绘制标题
    int title_x = 190;
    int title_y = 30;
    Send_Xstr(title_x, title_y, 200, 40, 3, BLUE, BLACK, 1, 1, 3, (char*)ui_states[STATE_WORK_MODE].title);
    
    // 绘制菜单项
    int item_x = 150;
    int start_y = 100;
    int item_height = 50;
    int current_selection = menu_selections[STATE_WORK_MODE];
    
    for (int i = 0; i < ui_states[STATE_WORK_MODE].item_count; i++) {
        int y = start_y + i * item_height;
        
        if (i == current_selection) {
            // 选中项显示箭头和高亮
            Send_Xstr(110, y, 35, 35, 2, RED, BLACK, 0, 1, 3, "\"->\"");
            Send_Xstr(item_x, y, 250, 35, 2, RED, BLACK, 0, 1, 3, (char*)ui_states[STATE_WORK_MODE].menu_items[i]);
        } else {
            Send_Xstr(item_x, y, 250, 35, 2, WHITE, BLACK, 0, 1, 3, (char*)ui_states[STATE_WORK_MODE].menu_items[i]);
        }
    }
    
    // 绘制底部提示
    Send_Xstr(120, 280, 280, 35, 1, YELLOW, BLACK, 0, 1, 3, "\"[↑↓]选择 [确认]选择 [返回]退出\"");
}

/**
 * @brief 绘制控制器参数菜单
 */
static void Draw_Controller(void)
{
    Screen_Clear(BLACK);
    
    // 绘制标题
    int title_x = 190;
    int title_y = 30;
    Send_Xstr(title_x, title_y, 200, 40, 3, BLUE, BLACK, 1, 1, 3, (char*)ui_states[STATE_CONTROLLER].title);
    
    // 绘制菜单项
    int item_x = 150;
    int start_y = 100;
    int item_height = 50;
    int current_selection = menu_selections[STATE_CONTROLLER];
    
    for (int i = 0; i < ui_states[STATE_CONTROLLER].item_count; i++) {
        int y = start_y + i * item_height;
        
        if (i == current_selection) {
            // 选中项显示箭头和高亮
            Send_Xstr(110, y, 35, 35, 2, RED, BLACK, 0, 1, 3, "\"->\"");
            Send_Xstr(item_x, y, 250, 35, 2, RED, BLACK, 0, 1, 3, (char*)ui_states[STATE_CONTROLLER].menu_items[i]);
        } else {
            Send_Xstr(item_x, y, 250, 35, 2, WHITE, BLACK, 0, 1, 3, (char*)ui_states[STATE_CONTROLLER].menu_items[i]);
        }
    }
    
    // 绘制底部提示
    Send_Xstr(120, 280, 280, 35, 1, YELLOW, BLACK, 0, 1, 3, "\"[↑↓]选择 [确认]进入 [返回]退出\"");
}

/**
 * @brief 处理主菜单按键
 */
static void Handle_Main_Menu_Keys(KeyEvent key_event)
{
    if (key_event.event_type == KEY_EVENT_SHORT_PRESS) {
        int current_selection = menu_selections[STATE_MAIN_MENU];
        
        switch (key_event.key_id) {
            case KEY_ID_UP:
                if (current_selection > 0) {
                    menu_selections[STATE_MAIN_MENU]--;
                    Draw_Main_Menu();
                }
                break;
                
            case KEY_ID_DOWN:
                if (current_selection < ui_states[STATE_MAIN_MENU].item_count - 1) {
                    menu_selections[STATE_MAIN_MENU]++;
                    Draw_Main_Menu();
                }
                break;
                
            case KEY_ID_ENTER:
            case KEY_ID_FOR:
                // 根据选择切换状态
                switch (current_selection) {
                    case 0:
                        State_Change(STATE_WORK_PARAMS);
                        break;
                    case 1:
                        State_Change(STATE_WORK_MODE);
                        break;
                    case 2:
                        State_Change(STATE_CONTROLLER);
                        break;
                }
                break;
                
            case KEY_ID_BACK:
                // 主菜单不处理返回
                break;
                
            default:
                break;
        }
    }
}

/**
 * @brief 处理工作参数按键
 */
static void Handle_Work_Params_Keys(KeyEvent key_event)
{
    if (key_event.event_type == KEY_EVENT_SHORT_PRESS) {
        int current_selection = menu_selections[STATE_WORK_PARAMS];
        
        if (is_editing) {
            // 编辑模式下的按键处理
            switch (key_event.key_id) {
                case KEY_ID_UP:
                    // 参数增加
                    // TODO: 加入实际的参数调整逻辑
                    Draw_Work_Params();
                    break;
                    
                case KEY_ID_DOWN:
                    // 参数减少
                    // TODO: 加入实际的参数调整逻辑
                    Draw_Work_Params();
                    break;
                    
                case KEY_ID_ENTER:
                case KEY_ID_FOR:
                    // 完成编辑
                    is_editing = false;
                    Draw_Work_Params();
                    break;
                    
                case KEY_ID_BACK:
                    // 取消编辑
                    is_editing = false;
                    Draw_Work_Params();
                    break;
                    
                default:
                    break;
            }
        } else {
            // 非编辑模式下的按键处理
            switch (key_event.key_id) {
                case KEY_ID_UP:
                    if (current_selection > 0) {
                        menu_selections[STATE_WORK_PARAMS]--;
                        Draw_Work_Params();
                    }
                    break;
                    
                case KEY_ID_DOWN:
                    if (current_selection < ui_states[STATE_WORK_PARAMS].item_count - 1) {
                        menu_selections[STATE_WORK_PARAMS]++;
                        Draw_Work_Params();
                    }
                    break;
                    
                case KEY_ID_ENTER:
                case KEY_ID_FOR:
                    if (current_selection == ui_states[STATE_WORK_PARAMS].item_count - 1) {
                        // "保存退出"选项
                        State_Change(STATE_MAIN_MENU);
                    } else {
                        // 其他选项进入编辑模式
                        is_editing = true;
                        Draw_Work_Params();
                    }
                    break;
                    
                case KEY_ID_BACK:
                    State_Handle_Back();
                    break;
                    
                default:
                    break;
            }
        }
    }
}

/**
 * @brief 处理工作模式按键
 */
static void Handle_Work_Mode_Keys(KeyEvent key_event)
{
    if (key_event.event_type == KEY_EVENT_SHORT_PRESS) {
        int current_selection = menu_selections[STATE_WORK_MODE];
        
        switch (key_event.key_id) {
            case KEY_ID_UP:
                if (current_selection > 0) {
                    menu_selections[STATE_WORK_MODE]--;
                    Draw_Work_Mode();
                }
                break;
                
            case KEY_ID_DOWN:
                if (current_selection < ui_states[STATE_WORK_MODE].item_count - 1) {
                    menu_selections[STATE_WORK_MODE]++;
                    Draw_Work_Mode();
                }
                break;
                
            case KEY_ID_ENTER:
            case KEY_ID_FOR:
                // 选择当前模式并返回
                // TODO: 保存选择的模式
                State_Change(STATE_MAIN_MENU);
                break;
                
            case KEY_ID_BACK:
                State_Handle_Back();
                break;
                
            default:
                break;
        }
    }
}

/**
 * @brief 处理控制器参数按键
 */
static void Handle_Controller_Keys(KeyEvent key_event)
{
    if (key_event.event_type == KEY_EVENT_SHORT_PRESS) {
        int current_selection = menu_selections[STATE_CONTROLLER];
        
        switch (key_event.key_id) {
            case KEY_ID_UP:
                if (current_selection > 0) {
                    menu_selections[STATE_CONTROLLER]--;
                    Draw_Controller();
                }
                break;
                
            case KEY_ID_DOWN:
                if (current_selection < ui_states[STATE_CONTROLLER].item_count - 1) {
                    menu_selections[STATE_CONTROLLER]++;
                    Draw_Controller();
                }
                break;
                
            case KEY_ID_ENTER:
            case KEY_ID_FOR:
                if (current_selection == ui_states[STATE_CONTROLLER].item_count - 1) {
                    // "返回主菜单"选项
                    State_Change(STATE_MAIN_MENU);
                } else {
                    // TODO: 处理其他子菜单项
                }
                break;
                
            case KEY_ID_BACK:
                State_Handle_Back();
                break;
                
            default:
                break;
        }
    }
} 