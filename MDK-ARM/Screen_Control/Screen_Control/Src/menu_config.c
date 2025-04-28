#include "menu_config.h"
#include <stddef.h>

// 定义菜单大小常量
#define WORK_MODE_SIZE 6
#define WORK_PARAMS_SIZE 7
#define CTRL_PARAMS_SIZE 10
#define MAIN_MENU_SIZE 3

// 工作模式子菜单项
const MenuItem work_mode_items[WORK_MODE_SIZE] = {
    {"1. 自动关", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"2. 自动开", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"3. 慢速真空控制", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"4. 真空压力控制", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"5. 阀门开度控制", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"6. 阀门开度保持", MENU_TYPE_ACTION, NULL, NULL, 0}
};
const uint8_t work_mode_size = WORK_MODE_SIZE;

// 工作参数子菜单项
const MenuItem work_params_items[WORK_PARAMS_SIZE] = {
    {"1. 压力单位设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"2. 控压PID设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"3. 位置环PID设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"4. 阀门全关值设置", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"5. 零点校准", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"6. REMOTE检查", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"7. 错误记录", MENU_TYPE_ACTION, NULL, NULL, 0}
};
const uint8_t work_params_size = WORK_PARAMS_SIZE;

// 控制器参数子菜单项
const MenuItem ctrl_params_items[CTRL_PARAMS_SIZE] = {
    {"1. 传感器量程设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"2. 联锁参数设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"3. 通信设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"4. 网口设置", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"5. 传感器信号偏置", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"6. 模拟量输入校准", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"7. 模拟量输入信号偏置", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"8. 恢复默认", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"9. 控制器默认值设置", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"10. 开关计数阀值设置", MENU_TYPE_ACTION, NULL, NULL, 0}
};
const uint8_t ctrl_params_size = CTRL_PARAMS_SIZE;

// 主菜单项
const MenuItem main_menu_items[MAIN_MENU_SIZE] = {
    {"1. 工作模式选择", MENU_TYPE_SUBMENU, NULL, work_mode_items, work_mode_size},
    {"2. 工作参数设置", MENU_TYPE_SUBMENU, NULL, work_params_items, work_params_size},
    {"3. 控制器参数", MENU_TYPE_SUBMENU, NULL, ctrl_params_items, ctrl_params_size}
};
const uint8_t main_menu_size = MAIN_MENU_SIZE; 