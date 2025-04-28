#ifndef __MENU_CONFIG_H
#define __MENU_CONFIG_H

#include <stdint.h>

// 菜单项类型枚举
typedef enum {
    MENU_TYPE_ACTION,    // 动作菜单项
    MENU_TYPE_SUBMENU    // 子菜单项
} MenuItemType;

// 菜单项结构体
typedef struct MenuItem {
    const char* text;            // 菜单项文本
    MenuItemType type;           // 菜单项类型
    void (*action)(void);        // 动作函数指针
    const struct MenuItem* submenu;  // 子菜单指针
    uint8_t submenu_size;        // 子菜单大小
} MenuItem;

// 菜单项数组声明
extern const MenuItem main_menu_items[];
extern const MenuItem work_mode_items[];
extern const MenuItem work_params_items[];
extern const MenuItem ctrl_params_items[];

// 菜单大小声明
extern const uint8_t main_menu_size;
extern const uint8_t work_mode_size;
extern const uint8_t work_params_size;
extern const uint8_t ctrl_params_size;

#endif /* __MENU_CONFIG_H */ 