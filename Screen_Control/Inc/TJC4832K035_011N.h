#ifndef __TJC4832K035_011N_H
#define __TJC4832K035_011N_H

#include "config.h"
#include <stdbool.h>

#define SCREEN      11314

#define RED       63488   // 红色
#define BLUE      31      // 蓝色  
#define GRAY      33840   // 灰色
#define BLACK     0       // 黑色
#define WHITE     65535   // 白色
#define GREEN     2016    // 绿色
#define BROWN     48192   // 橙色
#define YELLOW    65504   // 黄色


void Screen_Clear(uint16_t color);
void Send_Xstr(uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
			   uint16_t fontid, uint16_t point_color, uint16_t back_color,
			   uint8_t x_center, uint8_t y_center, uint8_t sta, char *text);
void Set_Screen_Sleep(bool is_sleep);

#endif

