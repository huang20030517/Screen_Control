#include "state.h"

void Handle_Main_Keys(KeyEvent event);

void Handle_Work_Mode_Keys(KeyEvent event);
void Handle_Work_Params_Keys(KeyEvent event);
void Handle_Ctrl_Params_Keys(KeyEvent event);

MenuContext g_menu = {0};

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
    if (event.key_id == KEY_ID_DOWN && g_menu.cursor_pos < 2)
        g_menu.cursor_pos++;
    else if (event.key_id == KEY_ID_UP && g_menu.cursor_pos > 0)
        g_menu.cursor_pos--;
    else if (event.key_id == KEY_ID_FOR)
    {
        // 根据光标位置进入二级菜单
        g_menu.prev_states[g_menu.stack_depth++] = STATE_MAIN;
        g_menu.current = (g_menu.cursor_pos == 0) ? STATE_WORK_MODE : (g_menu.cursor_pos == 1) ? STATE_WORK_PARAMS
                                                                                               : STATE_CTRL_PARAMS;
        g_menu.cursor_pos = 0; // 重置子菜单光标
    }
}

/// @brief 二级菜 单工作模式 菜单按键处理
/// @param event 按键事件
void Handle_Work_Mode_Keys(KeyEvent event)
{
    
}

/// @brief 二级菜单 工作参数 菜单按键处理
/// @param event 按键事件
void Handle_Work_Params_Keys(KeyEvent event)
{
}

/// @brief 二级菜单 控制器参数设置 菜单按键处理
/// @param event 按键事件
void Handle_Ctrl_Params_Keys(KeyEvent event)
{
}
