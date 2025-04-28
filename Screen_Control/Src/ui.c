#include "ui.h"
#include "state.h"
#include "TJC4832K035_011N.h"
#include "menu_draw.h"
#include <string.h>

void UI_Init(void)
{
    Key_Init();
    Menu_State_Init();
    
    Screen_Clear(LIGHT_BLUE);
    Draw_Menu();
}

/**
 * @brief 根据菜单状态绘制对应的菜单界面
 * @param state 菜单状态
 */
void Draw_Menu_State(MenuState state)
{
    switch (state)
    {
    case STATE_MAIN:
        Draw_Menu();
        break;
    case STATE_WORK_MODE:
        Draw_Work_Mode_Menu();
        break;
    case STATE_WORK_PARAMS:
        Draw_Work_Params_Menu();
        break;
    case STATE_CTRL_PARAMS:
        Draw_Controller_Menu();
        break;
    default:
        break;
    }
}

void UI_Task(void)
{
    static MenuState last_state = STATE_COUNT;
    static int8_t last_cursor_pos = -1;
    static int8_t last_page = -1;

    // 获取按键并处理
    KeyEvent event = Key_Scan();

    // 保存当前状态
    MenuContext *menu = Get_Menu_Context();
    MenuState current_state = menu->current;
    int8_t current_cursor_pos = menu->cursor_pos;
    int8_t current_page = current_cursor_pos / 5;

    // 处理按键
    Handle_Menu_Key(event);

    // 检查状态变化并更新界面
    if (menu->current != current_state)
    {
        // 菜单状态改变，完全重绘
        Draw_Menu_State(menu->current);
        last_state = menu->current;
        last_cursor_pos = menu->cursor_pos;
        last_page = menu->cursor_pos / 5;
    }
    else if (menu->cursor_pos != current_cursor_pos)
    {
        int8_t new_page = menu->cursor_pos / 5;

        if (new_page != current_page)
        {
            // 页面变化，重绘
            Draw_Menu_State(menu->current);
            last_page = new_page;
        }
        else
        {
            // 同页光标变化，只更新箭头
            Update_Menu_Arrow(menu->current, last_cursor_pos, menu->cursor_pos);
        }

        last_cursor_pos = menu->cursor_pos;
    }

    HAL_Delay(20);
}