#ifndef __MENU_DRAW_H
#define __MENU_DRAW_H

#include <stdint.h>
#include "state.h"

/**
 * @brief 在指定位置绘制带选中状态的菜单项
 * @param x 菜单项起始 X 坐标（区域左上角）
 * @param y 菜单项起始 Y 坐标（区域左上角）
 * @param text 菜单项文本
 * @param is_selected 是否被选中
 * @param font_size 字体大小ID
 * @param item_height 菜单项高度
 */
void Draw_Menu_Item(uint16_t x, uint16_t y, const char *text, uint8_t is_selected, uint8_t font_size, uint16_t item_height);

/**
 * @brief 绘制菜单标题
 * @param title 标题文本
 */
void Draw_Title(const char *title);

/**
 * @brief 绘制主菜单（一级菜单）
 */
void Draw_Menu(void);

/**
 * @brief 绘制工作模式菜单（二级菜单）
 */
void Draw_Work_Mode_Menu(void);

/**
 * @brief 绘制工作参数菜单（二级菜单）
 */
void Draw_Work_Params_Menu(void);

/**
 * @brief 绘制控制器参数菜单（二级菜单）
 */
void Draw_Controller_Menu(void);

/**
 * @brief 根据菜单状态绘制对应的菜单界面
 * @param state 菜单状态
 */
void Draw_Menu_State(MenuState state);

/**
 * @brief 只更新菜单项的箭头，不重绘整个菜单
 * @param menu_type 菜单类型
 * @param old_pos 旧光标位置
 * @param new_pos 新光标位置
 */
void Update_Menu_Arrow(MenuState menu_type, int old_pos, int new_pos);

#endif // __MENU_DRAW_H