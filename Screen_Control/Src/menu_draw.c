#include "menu_draw.h"
#include "TJC4832K035_011N.h"
#include <string.h>

/*-------------------------- ���泣�� --------------------------*/
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320
#define FONT_WIDTH 16  // ÿ���ַ���ȣ����أ�
#define FONT_HEIGHT 35 // ÿ���ַ��߶ȣ����أ�

// һ���˵�����
static const char *main_menu_items[] = {
    "1. ����ģʽѡ��",
    "2. ������������",
    "3. ����������"};

// ����ģʽ�˵�����
static const char *work_mode_menu_items[] = {
    "1. �Զ���",
    "2. �Զ���",
    "3. ������տ���",
    "4. ���ѹ������",
    "5. ���ſ��ȿ���",
    "6. ���ſ��ȱ���"};

// ���������˵�����
static const char *work_params_menu_items[] = {
    "1. ѹ����λ����",
    "2. ��ѹPID����",
    "3. λ�û�PID����",
    "4. ����ȫ��ֵ����",
    "5. ���У׼",
    "6. REMOTE���",
    "7. �����¼"};

// �����������˵�����
static const char *ctrl_params_menu_items[] = {
    " 1. ��������������",
    " 2. ������������",
    " 3. ͨ������",
    " 4. ��������",
    " 5. �������ź�ƫ��",
    " 6. ģ��������У׼",
    " 7. ģ���������ź�ƫ��",
    " 8. �ָ�Ĭ��",
    " 9. ������Ĭ��ֵ����",
    "10. ���ؼ�����ֵ����"};
/**
 * @brief ���Ʋ˵�����
 * @param title �����ı�
 */
void Draw_Title(const char *title)
{
    uint16_t title_width = strlen(title) * FONT_WIDTH * 1.5; // �ʵ���������������
    uint16_t title_x = (SCREEN_WIDTH - title_width) / 2;

    // ���������ŵı����ַ���
    char quoted_title[32];
    snprintf(quoted_title, sizeof(quoted_title), "\"%s\"", title);

    // ʹ���еȴ�С����(fontid=2)������ˮƽ����(xcenter=1)�ʹ�ֱ����(ycenter=1)
    Send_Xstr(title_x, 20, title_width, FONT_HEIGHT * 1.2, 2, BLACK, LIGHT_BLUE, 1, 1, 1, quoted_title);
}

/**
 * @brief ��ָ��λ�û��ƴ�ѡ��״̬�Ĳ˵���
 * @param x �˵�����ʼ X ���꣨�������Ͻǣ�
 * @param y �˵�����ʼ Y ���꣨�������Ͻǣ�
 * @param text �˵����ı�
 * @param is_selected �Ƿ�ѡ��
 * @param font_size �����СID
 * @param item_height �˵���߶�
 */
void Draw_Menu_Item(uint16_t x, uint16_t y, const char *text, uint8_t is_selected, uint8_t font_size, uint16_t item_height)
{
    // ��ͷ���
    const uint16_t arrow_width = 30;

    // ���Ƽ�ͷָʾ��ǰѡ���y����ж��룩
    if (is_selected)
    {
        Send_Xstr(x, y, arrow_width, item_height, font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\"��\"");
    }
    else
    {
        Send_Xstr(x, y, arrow_width, item_height, font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\" \"");
    }

    // ���Ʋ˵����ı�������룬y����ж��룩
    char quoted_text[64];
    snprintf(quoted_text, sizeof(quoted_text), "\"%s\"", text);

    // �ı�����Ӽ�ͷ�����Ҳ࿪ʼ���������Ӧ
    Send_Xstr(x + arrow_width, y, SCREEN_WIDTH - x - arrow_width - 10, item_height,
              font_size, BLACK, LIGHT_BLUE, 0, 1, 1, quoted_text);
}

/**
 * @brief ���ƶ����˵�ͨ�ý���
 * @param title �˵�����
 * @param items �˵�������
 * @param item_count �˵�������
 * @param selected_index ��ǰѡ�еĲ˵�������
 */
static void Draw_Submenu(const char *title, const char **items, int item_count, int selected_index)
{
    // �����˵�����
    const uint8_t sub_font_size = 0;      // �����˵������С
    const uint16_t sub_left_margin = 110; // �����˵���߾��С
    const uint16_t sub_start_y = 75;      // �����˵���ʼY����
    const uint16_t sub_item_height = 35;  // �����˵���߶�

    // ��������ɫ����
    Screen_Clear(LIGHT_BLUE);

    // ���Ʊ���
    Draw_Title(title);

    // ����ÿҳ��ʾ�Ĳ˵�������
    const int items_per_page = 5;

    // ���㵱ǰҳ
    int current_page = selected_index / items_per_page;

    // �����ҳ��һ���˵��������
    int first_item_index = current_page * items_per_page;

    // �����ҳ�Ĳ˵�������
    int page_item_count = (item_count - first_item_index < items_per_page) ? (item_count - first_item_index) : items_per_page;

    // ���Ƶ�ǰҳ�Ĳ˵���
    for (int i = 0; i < page_item_count; i++)
    {
        int item_index = first_item_index + i;
        Draw_Menu_Item(sub_left_margin, sub_start_y + i * sub_item_height,
                       items[item_index],
                       item_index == selected_index,
                       sub_font_size, sub_item_height);
    }

    // ���ҳ��ָʾ����ʾ��ǰҳ/��ҳ����
    if (item_count > items_per_page)
    {
        int total_pages = (item_count + items_per_page - 1) / items_per_page;
        char page_info[20];
        snprintf(page_info, sizeof(page_info), "\"%d/%d\"", current_page + 1, total_pages);
        // ���½���ʾҳ�룬�Ҷ���(xcenter=2)
        Send_Xstr(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 30, 50, 20, 1, BLACK, LIGHT_BLUE, 2, 1, 1, page_info);
    }
}

/**
 * @brief �������˵���һ���˵���
 */
void Draw_Menu(void)
{
    MenuContext *menu = Get_Menu_Context();

    // һ���˵�����
    const uint8_t main_font_size = 2;     // һ���˵�ʹ�ø�������
    const uint16_t main_left_margin = 90; // һ���˵���߾�
    const uint16_t main_start_y = 90;     // һ���˵���ʼY����
    const uint16_t main_item_height = 50; // һ���˵���߶�

    // ��������ɫ����
    Screen_Clear(LIGHT_BLUE);

    // ���Ʊ���
    Draw_Title("���˵�");

    // ���Ʋ˵��һ���˵�����٣�����Ҫ��ҳ��
    for (int i = 0; i < 3; i++)
    {
        // Ϊ���˵�������Ƽ�ͷ��ʹ�ø��������
        uint16_t x = main_left_margin;
        uint16_t y = main_start_y + i * main_item_height;

        // ���Ƽ�ͷ��ո�ʹ�������˵�������ͬ�Ĵ�С��
        if (i == menu->cursor_pos)
        {
            Send_Xstr(x, y, 40, main_item_height, main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\"��\"");
        }
        else
        {
            Send_Xstr(x, y, 40, main_item_height, main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\" \"");
        }

        // ���Ʋ˵����ı�
        char quoted_text[64];
        snprintf(quoted_text, sizeof(quoted_text), "\"%s\"", main_menu_items[i]);

        // ʹ����ͬ�Ĵ�����
        Send_Xstr(x + 40, y, SCREEN_WIDTH - x - 50, main_item_height,
                  main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, quoted_text);
    }
}

/**
 * @brief ���ƹ���ģʽ�˵��������˵���
 */
void Draw_Work_Mode_Menu(void)
{
    MenuContext *menu = Get_Menu_Context();
    Draw_Submenu("����ģʽѡ��", work_mode_menu_items, 6, menu->cursor_pos);
}

/**
 * @brief ���ƹ��������˵��������˵���
 */
void Draw_Work_Params_Menu(void)
{
    MenuContext *menu = Get_Menu_Context();
    Draw_Submenu("������������", work_params_menu_items, 7, menu->cursor_pos);
}

/**
 * @brief ���ƿ����������˵��������˵���
 */
void Draw_Controller_Menu(void)
{
    MenuContext *menu = Get_Menu_Context();
    Draw_Submenu("��������������", ctrl_params_menu_items, 10, menu->cursor_pos);
}

/**
 * @brief ֻ���²˵���ļ�ͷ�����ػ������˵�
 * @param menu_type �˵�����
 * @param old_pos �ɹ��λ�ã�ȫ��λ�ã�
 * @param new_pos �¹��λ�ã�ȫ��λ�ã�
 */
void Update_Menu_Arrow(MenuState menu_type, int old_pos, int new_pos)
{
    uint8_t font_size;
    uint16_t left_margin, start_y, item_height, arrow_width;
    int page_old_pos, page_new_pos;
    int current_page = new_pos / 5; // ���㵱ǰҳ��

    // ���ݲ˵��������ò���
    if (menu_type == STATE_MAIN)
    {
        font_size = 2;
        left_margin = 90;
        start_y = 90;
        item_height = 50;
        arrow_width = 40;

        // ���˵�����Ҫ����ҳ��λ��
        page_old_pos = old_pos;
        page_new_pos = new_pos;
    }
    else
    {
        font_size = 0;
        left_margin = 110;
        start_y = 75;
        item_height = 35;
        arrow_width = 30;

        // �����˵���Ҫ����ҳ�����λ��
        page_old_pos = old_pos % 5; // ����ҳ��λ��
        page_new_pos = new_pos % 5; // ����ҳ��λ��
    }

    // ����ɼ�ͷ
    uint16_t old_y = start_y + page_old_pos * item_height;
    Send_Xstr(left_margin, old_y, arrow_width, item_height,
              font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\" \"");

    // �����¼�ͷ
    uint16_t new_y = start_y + page_new_pos * item_height;
    Send_Xstr(left_margin, new_y, arrow_width, item_height,
              font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\"��\"");
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