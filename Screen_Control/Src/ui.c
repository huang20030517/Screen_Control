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
 * @brief ���ݲ˵�״̬���ƶ�Ӧ�Ĳ˵�����
 * @param state �˵�״̬
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

    // ��ȡ����������
    KeyEvent event = Key_Scan();

    // ���浱ǰ״̬
    MenuContext *menu = Get_Menu_Context();
    MenuState current_state = menu->current;
    int8_t current_cursor_pos = menu->cursor_pos;
    int8_t current_page = current_cursor_pos / 5;

    // ������
    Handle_Menu_Key(event);

    // ���״̬�仯�����½���
    if (menu->current != current_state)
    {
        // �˵�״̬�ı䣬��ȫ�ػ�
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
            // ҳ��仯���ػ�
            Draw_Menu_State(menu->current);
            last_page = new_page;
        }
        else
        {
            // ͬҳ���仯��ֻ���¼�ͷ
            Update_Menu_Arrow(menu->current, last_cursor_pos, menu->cursor_pos);
        }

        last_cursor_pos = menu->cursor_pos;
    }

    HAL_Delay(20);
}