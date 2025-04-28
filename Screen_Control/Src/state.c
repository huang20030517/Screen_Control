#include "state.h"

void Handle_Main_Keys(KeyEvent event);

void Handle_Work_Mode_Keys(KeyEvent event);
void Handle_Work_Params_Keys(KeyEvent event);
void Handle_Ctrl_Params_Keys(KeyEvent event);

MenuContext g_menu = {0};

/**
 * @brief 初始化菜单状态
 */
void Menu_State_Init(void)
{
    g_menu.current = STATE_MAIN; // 初始状态为主菜单
    g_menu.stack_depth = 0;      // 初始堆栈深度为0
    g_menu.cursor_pos = 0;       // 初始光标位置为0
}

/**
 * @brief 处理菜单状态切换
 * @param event 按键事件
 */
void Handle_Menu_Key(KeyEvent event)
{
    switch (g_menu.current)
    {
    //---------------- 一级菜单处理 ----------------//
    case STATE_MAIN:
        Handle_Main_Keys(event);
        break;

    //---------------- 二级菜单处理 ----------------//
    case STATE_WORK_MODE:
        Handle_Work_Mode_Keys(event);
        break;
    case STATE_WORK_PARAMS:
        Handle_Work_Params_Keys(event);
        break;
    case STATE_CTRL_PARAMS:
        Handle_Ctrl_Params_Keys(event);
        break;

    default:
        break;
    }
}

void Handle_Main_Keys(KeyEvent event)
{
    switch (event.key_id)
    {
    case KEY_ID_UP:
        if (g_menu.cursor_pos > 0)
        {
            g_menu.cursor_pos--;
        }

        break;
    case KEY_ID_DOWN:
        if (g_menu.cursor_pos < 2)
        {
            g_menu.cursor_pos++;
        }
        break;
    case KEY_ID_FOR:
        // 存储当前状态数据
        g_menu.prev_states[g_menu.stack_depth++] = STATE_MAIN;

        // 进入二级菜单
        switch (g_menu.cursor_pos)
        {
        case 0:
            g_menu.current = STATE_WORK_MODE;
            break;
        case 1:
            g_menu.current = STATE_WORK_PARAMS;
            break;
        case 2:
            g_menu.current = STATE_CTRL_PARAMS;
            break;
        }

        g_menu.cursor_pos = 0;
    default:
        break;
    }
}

/// @brief 二级菜单 工作模式 菜单按键处理
/// @param event 按键事件
void Handle_Work_Mode_Keys(KeyEvent event)
{

    switch (event.key_id)
    {

    case KEY_ID_UP:
        if (g_menu.cursor_pos > 0)
        {
            g_menu.cursor_pos--;
        }
        break;
    case KEY_ID_DOWN:
        if (g_menu.cursor_pos < 5)
        {
            g_menu.cursor_pos++;
        }
        break;
    case KEY_ID_FOR:
        // 存储当前状态数据
        g_menu.prev_states[g_menu.stack_depth++] = STATE_WORK_MODE;

        // 进入三级菜单
        switch (g_menu.cursor_pos)
        {
        case 0:
            g_menu.current = STATE_WORK_MODE_AUTO_OFF;
            break;
        case 1:
            g_menu.current = STATE_WORK_MODE_AUTO_ON;
            break;
        case 2:
            g_menu.current = STATE_WORK_MODE_SLOW_CTRL;
            break;
        case 3:
            g_menu.current = STATE_WORK_MODE_REAL_PRESS;
            break;
        case 4:
            g_menu.current = STATE_WORK_MODE_VALVE_OPEN;
            break;
        case 5:
            g_menu.current = STATE_WORK_MODE_VALVE_HOLD;

        default:
            break;
        }

        break;
    case KEY_ID_BACK:
        if (g_menu.stack_depth > 0)
        {
            // 返回上一级
            g_menu.current = g_menu.prev_states[--g_menu.stack_depth];
            g_menu.cursor_pos = 0;
        }
    default:
        break;
    }
}
void Handle_Work_Params_Keys(KeyEvent event)
{
    switch (event.key_id)
    {
    case KEY_ID_DOWN:
        if (g_menu.cursor_pos < 6)
        {
            g_menu.cursor_pos++;
        }
        break;

    case KEY_ID_UP:
        if (g_menu.cursor_pos > 0)
        {
            g_menu.cursor_pos--;
        }
        break;

    case KEY_ID_FOR:
    {
        // 保存当前状态并进入三级菜单
        g_menu.prev_states[g_menu.stack_depth++] = STATE_WORK_PARAMS;

        // 根据光标位置选择子状态
        switch (g_menu.cursor_pos)
        {
        case 0:
            g_menu.current = STATE_WORK_MODE_AUTO_OFF;
            break;
        case 1:
            g_menu.current = STATE_WORK_MODE_AUTO_ON;
            break;
        case 2:
            g_menu.current = STATE_WORK_MODE_SLOW_CTRL;
            break;
        case 3:
            g_menu.current = STATE_WORK_MODE_REAL_PRESS;
            break;
        case 4:
            g_menu.current = STATE_WORK_MODE_VALVE_OPEN;
            break;
        case 5:
            g_menu.current = STATE_WORK_MODE_VALVE_HOLD;
            break;
        default:
            break;
        }
        g_menu.cursor_pos = 0; // 重置三级菜单光标
        break;
    }

    case KEY_ID_BACK:
        if (g_menu.stack_depth > 0)
        {
            // 返回主菜单并恢复光标位置
            g_menu.current = g_menu.prev_states[--g_menu.stack_depth];
            g_menu.cursor_pos = 1; // 主菜单第二项（工作参数）
        }
        break;

    default:
        // 可选：处理未识别的按键
        break;
    }
}
/// @brief 二级菜单 控制器参数设置 菜单按键处理
/// @param event 按键事件
void Handle_Ctrl_Params_Keys(KeyEvent event)
{
    switch (event.key_id)
    {
    case KEY_ID_DOWN:
        if (g_menu.cursor_pos < 9)
        { // 允许 0-9 共10个菜单项
            g_menu.cursor_pos++;
        }
        break;

    case KEY_ID_UP:
        if (g_menu.cursor_pos > 0)
        {
            g_menu.cursor_pos--;
        }
        break;

    case KEY_ID_FOR:
    {
        // 保存当前状态并进入三级菜单
        g_menu.prev_states[g_menu.stack_depth++] = STATE_CTRL_PARAMS;

        switch (g_menu.cursor_pos)
        {
        case 0:
            g_menu.current = STATE_CTRL_SENSOR_RANGE;
            break;
        case 1:
            g_menu.current = STATE_CTRL_INTERLOCK_PARAMS;
            break;
        case 2:
            g_menu.current = STATE_CTRL_COMM_SETTING;
            break;
        case 3:
            g_menu.current = STATE_CTRL_NETWORK_SETTING;
            break;
        case 4:
            g_menu.current = STATE_CTRL_SENSOR_OFFSET;
            break;
        case 5:
            g_menu.current = STATE_CTRL_AI_CALIB;
            break;
        case 6:
            g_menu.current = STATE_CTRL_AI_OFFSET;
            break;
        case 7:
            g_menu.current = STATE_CTRL_RESTORE_DEFAULT;
            break;
        case 8:
            g_menu.current = STATE_CTRL_CNT_DEFAULT;
            break;
        case 9:
            g_menu.current = STATE_CTRL_SWITCH_COUNT_THRESHOLD;
            break;
        default:
            break;
        }
        g_menu.cursor_pos = 0; // 重置三级菜单光标
        break;
    }

    case KEY_ID_BACK:
        if (g_menu.stack_depth > 0)
        {
            // 返回主菜单并恢复光标位置
            g_menu.current = g_menu.prev_states[--g_menu.stack_depth];
            g_menu.cursor_pos = 2; // 主菜单第三项（控制器参数）
        }
        break;

    default:
        break;
    }
}

/**
 * @brief 获取菜单上下文指针，供UI模块使用
 * @return 返回菜单上下文的指针
 */
MenuContext *Get_Menu_Context(void)
{
    return &g_menu;
}
