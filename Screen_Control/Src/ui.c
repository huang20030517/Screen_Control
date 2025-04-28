#include "ui.h"
#include "state.h"
#include "TJC4832K035_011N.h"
#include <string.h>

/*-------------------------- 界面常量 --------------------------*/
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320
#define FONT_WIDTH 16  // 每个字符宽度（像素）
#define FONT_HEIGHT 35 // 每个字符高度（像素）


/*-------------------------- 菜单项内容 --------------------------*/
// 一级菜单内容
static const char *main_menu_items[] = {
    "1. 工作模式选择",
    "2. 工作参数设置",
    "3. 控制器参数"};

// 工作模式菜单内容
static const char *work_mode_menu_items[] = {
    "1. 自动关",
    "2. 自动开",
    "3. 慢速真空控制",
    "4. 真空压力控制",
    "5. 阀门开度控制",
    "6. 阀门开度保持"};

// 工作参数菜单内容
static const char *work_params_menu_items[] = {
    "1. 压力单位设置",
    "2. 控压PID设置",
    "3. 位置环PID设置",
    "4. 阀门全关值设置",
    "5. 零点校准",
    "6. REMOTE检查",
    "7. 错误记录"};

// 控制器参数菜单内容
static const char *ctrl_params_menu_items[] = {
    "1. 传感器量程设置",
    "2. 联锁参数设置",
    "3. 通信设置",
    "4. 网口设置",
    "5. 传感器信号偏置",
    "6. 模拟量输入校准",
    "7. 模拟量输入信号偏置",
    "8. 恢复默认",
    "9. 控制器默认值设置",
    "10. 开关计数阀值设置"};

/*-------------------------- 菜单绘制辅助函数 --------------------------*/
/**
 * @brief 绘制菜单标题
 * @param title 标题文本
 */
static void Draw_Title(const char* title)
{
    uint16_t title_width = strlen(title) * FONT_WIDTH * 1.5; // 适当调整标题区域宽度
    uint16_t title_x = (SCREEN_WIDTH - title_width) / 2;
    
    // 构建带引号的标题字符串
    char quoted_title[32];
    snprintf(quoted_title, sizeof(quoted_title), "\"%s\"", title);
    
    // 使用中等大小字体(fontid=2)，保持水平居中(xcenter=1)和垂直居中(ycenter=1)
    Send_Xstr(title_x, 20, title_width, FONT_HEIGHT * 1.2, 2, BLACK, LIGHT_BLUE, 1, 1, 1, quoted_title);
}

/**
 * @brief 在指定位置绘制带选中状态的菜单项
 * @param x 菜单项起始 X 坐标（区域左上角）
 * @param y 菜单项起始 Y 坐标（区域左上角）
 * @param text 菜单项文本
 * @param is_selected 是否被选中
 * @param font_size 字体大小ID
 * @param item_height 菜单项高度
 */
static void Draw_Menu_Item(uint16_t x, uint16_t y, const char* text, uint8_t is_selected, uint8_t font_size, uint16_t item_height)
{
    // 箭头宽度
    const uint16_t arrow_width = 30;
    
    // 绘制箭头指示当前选中项（y轴居中对齐）
    if (is_selected) {
        Send_Xstr(x, y, arrow_width, item_height, font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\"→\"");
    } else {
        Send_Xstr(x, y, arrow_width, item_height, font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\" \"");
    }
    
    // 绘制菜单项文本（左对齐，y轴居中对齐）
    char quoted_text[64];
    snprintf(quoted_text, sizeof(quoted_text), "\"%s\"", text);
    
    // 文本区域从箭头区域右侧开始，宽度自适应
    Send_Xstr(x + arrow_width, y, SCREEN_WIDTH - x - arrow_width - 10, item_height, 
              font_size, BLACK, LIGHT_BLUE, 0, 1, 1, quoted_text);
}

/**
 * @brief 绘制主菜单（一级菜单）
 */
void Draw_Menu(void)
{
    MenuContext* menu = Get_Menu_Context();
    
    // 一级菜单参数
    const uint8_t main_font_size = 2;           // 一级菜单使用更大字体
    const uint16_t main_left_margin = 90;       // 一级菜单左边距
    const uint16_t main_start_y = 90;           // 一级菜单起始Y坐标
    const uint16_t main_item_height = 50;       // 一级菜单项高度
    
    // 清屏，蓝色背景
    Screen_Clear(LIGHT_BLUE);
    
    // 绘制标题
    Draw_Title("主菜单");
    
    // 绘制菜单项（一级菜单项较少，不需要分页）
    for (int i = 0; i < 3; i++) {
        // 为主菜单项单独绘制箭头，使用更大的字体
        uint16_t x = main_left_margin;
        uint16_t y = main_start_y + i * main_item_height;
        
        // 绘制箭头或空格（使用与主菜单字体相同的大小）
        if (i == menu->cursor_pos) {
            Send_Xstr(x, y, 40, main_item_height, main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\"→\"");
        } else {
            Send_Xstr(x, y, 40, main_item_height, main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\" \"");
        }
        
        // 绘制菜单项文本
        char quoted_text[64];
        snprintf(quoted_text, sizeof(quoted_text), "\"%s\"", main_menu_items[i]);
        
        // 使用相同的大字体
        Send_Xstr(x + 40, y, SCREEN_WIDTH - x - 50, main_item_height, 
                main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, quoted_text);
    }
}

/**
 * @brief 绘制二级菜单通用界面
 * @param title 菜单标题
 * @param items 菜单项数组
 * @param item_count 菜单项数量
 * @param selected_index 当前选中的菜单项索引
 */
static void Draw_Submenu(const char* title, const char** items, int item_count, int selected_index)
{
    // 二级菜单参数
    const uint8_t sub_font_size = 0;           // 二级菜单字体较小
    const uint16_t sub_left_margin = 110;       // 二级菜单左边距较小
    const uint16_t sub_start_y = 75;           // 二级菜单起始Y坐标
    const uint16_t sub_item_height = 35;       // 二级菜单项高度
    
    // 清屏，蓝色背景
    Screen_Clear(LIGHT_BLUE);
    
    // 绘制标题
    Draw_Title(title);
    
    // 计算每页显示的菜单项数量
    const int items_per_page = 5;
    
    // 计算当前页
    int current_page = selected_index / items_per_page;
    
    // 计算该页第一个菜单项的索引
    int first_item_index = current_page * items_per_page;
    
    // 计算该页的菜单项数量
    int page_item_count = (item_count - first_item_index < items_per_page) ? 
                          (item_count - first_item_index) : items_per_page;
    
    // 绘制当前页的菜单项
    for (int i = 0; i < page_item_count; i++) {
        int item_index = first_item_index + i;
        Draw_Menu_Item(sub_left_margin, sub_start_y + i * sub_item_height, 
                      items[item_index], 
                      item_index == selected_index,
                      sub_font_size, sub_item_height);
    }
    
    // 添加页码指示（显示当前页/总页数）
    if (item_count > items_per_page) {
        int total_pages = (item_count + items_per_page - 1) / items_per_page;
        char page_info[20];
        snprintf(page_info, sizeof(page_info), "\"%d/%d\"", current_page + 1, total_pages);
        // 右下角显示页码，右对齐(xcenter=2)
        Send_Xstr(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 30, 50, 20, 1, BLACK, LIGHT_BLUE, 2, 1, 1, page_info);
    }
}

/**
 * @brief 绘制工作模式菜单（二级菜单）
 */
void Draw_Work_Mode_Menu(void)
{
    MenuContext* menu = Get_Menu_Context();
    Draw_Submenu("工作模式选择", work_mode_menu_items, 6, menu->cursor_pos);
}

/**
 * @brief 绘制工作参数菜单（二级菜单）
 */
void Draw_Work_Params_Menu(void)
{
    MenuContext* menu = Get_Menu_Context();
    Draw_Submenu("工作参数设置", work_params_menu_items, 7, menu->cursor_pos);
}

/**
 * @brief 绘制控制器参数菜单（二级菜单）
 */
void Draw_Controller_Menu(void)
{
    MenuContext* menu = Get_Menu_Context();
    Draw_Submenu("控制器参数设置", ctrl_params_menu_items, 10, menu->cursor_pos);
}

void UI_Init(void)
{
    Key_Init();
    Menu_State_Init(); // 初始化菜单状态
    Screen_Clear(LIGHT_BLUE);
    
    // 初始化界面
    Draw_Menu();
}

void UI_Task(void)
{
    static MenuState last_state = STATE_COUNT; // 初始化为无效状态，确保首次绘制
    static int8_t last_cursor_pos = -1;        // 跟踪光标变化
    static int8_t last_page = -1;              // 跟踪页面变化
    
    KeyEvent event = Key_Scan();
    
    // 处理按键前保存当前状态
    MenuContext* menu = Get_Menu_Context();
    MenuState current_state = menu->current;
    int8_t current_cursor_pos = menu->cursor_pos;
    int8_t current_page = current_cursor_pos / 5; // 计算当前页
    
    // 处理按键
    Handle_Menu_Key(event);
    
    // 检查状态变化
    if (menu->current != current_state) {
        // 菜单层级发生变化，完全重绘屏幕
        last_state = menu->current;
        last_cursor_pos = menu->cursor_pos;
        last_page = menu->cursor_pos / 5;
        
        // 根据当前菜单状态绘制界面
        switch (menu->current)
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
    else if (menu->cursor_pos != current_cursor_pos) {
        int8_t new_page = menu->cursor_pos / 5;
        
        if (menu->current == STATE_MAIN) {
            // 主菜单光标变化处理
            const uint8_t main_font_size = 2;
            const uint16_t main_left_margin = 90;
            const uint16_t main_start_y = 90;
            const uint16_t main_item_height = 50;
            
            // 清除上一个选中项的箭头
            uint16_t old_y = main_start_y + last_cursor_pos * main_item_height;
            Send_Xstr(main_left_margin, old_y, 40, main_item_height, 
                    main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\" \"");
            
            // 绘制新的选中项箭头
            uint16_t new_y = main_start_y + menu->cursor_pos * main_item_height;
            Send_Xstr(main_left_margin, new_y, 40, main_item_height, 
                    main_font_size, BLACK, LIGHT_BLUE, 0, 1, 1, "\"→\"");
            
            // 更新记录的光标位置
            last_cursor_pos = menu->cursor_pos;
        }
        else if (new_page != current_page) {
            // 二级菜单翻页，重绘整个菜单
            switch (menu->current)
            {
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
            
            last_page = new_page;
            last_cursor_pos = menu->cursor_pos;
        }
        else {
            // 二级菜单同页光标变化
            // 二级菜单参数
            const uint8_t sub_font_size = 0;           // 二级菜单字体较小
            const uint16_t sub_left_margin = 110;      // 二级菜单左边距较小
            const uint16_t sub_start_y = 75;           // 二级菜单起始Y坐标
            const uint16_t sub_item_height = 35;       // 二级菜单项高度
            
            const char** items;
            int item_count;
            
            // 根据当前菜单状态选择相应的菜单项
            switch (menu->current)
            {
            case STATE_WORK_MODE:
                items = work_mode_menu_items;
                item_count = 6;
                break;
            case STATE_WORK_PARAMS:
                items = work_params_menu_items;
                item_count = 7;
                break;
            case STATE_CTRL_PARAMS:
                items = ctrl_params_menu_items;
                item_count = 10;
                break;
            default:
                items = NULL;
                item_count = 0;
                break;
            }
            
            if (items && item_count > 0) {
                const int items_per_page = 5;
                // 计算页内索引
                int last_page_index = last_cursor_pos % items_per_page;
                int new_page_index = menu->cursor_pos % items_per_page;
                
                // 清除上一个选中项的箭头
                if (last_cursor_pos >= new_page * items_per_page && 
                    last_cursor_pos < (new_page + 1) * items_per_page) {
                    Draw_Menu_Item(sub_left_margin, sub_start_y + last_page_index * sub_item_height, 
                                 items[last_cursor_pos], 0, sub_font_size, sub_item_height);
                }
                
                // 绘制新的选中项
                Draw_Menu_Item(sub_left_margin, sub_start_y + new_page_index * sub_item_height, 
                             items[menu->cursor_pos], 1, sub_font_size, sub_item_height);
                
                // 更新记录的光标位置
                last_cursor_pos = menu->cursor_pos;
            }
        }
    }
    
    HAL_Delay(20);
}