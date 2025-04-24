/*
 * @Author: Huang
 * @Date: 2025-04-23 15:30:00
 * @LastEditTime: 2025-04-23 15:30:00
 * @FilePath: \Screen_Control\Src\TJC4832K035_011N.c
 * @Description:
 * 编写屏幕API
 * 480*320无触摸，系列 k0。
 */
#include "TJC4832K035_011N.h"

/* DMA传输状态检测宏（硬件级原子操作） */
#define UART_READY() (__HAL_UART_GET_FLAG(&SCREEN_USART_HANDLE, UART_FLAG_TC) != RESET)

/**
 * @brief 清屏
 * @param color 颜色
 */
void Screen_Clear(uint16_t color)
{
    static uint8_t dma_buffer[20]; // 静态缓冲区保障DMA数据安全

    // 生成基础命令（不含终止符）
    int cmd_len = snprintf((char *)dma_buffer, sizeof(dma_buffer), "cls %d", color);

    // 安全添加终止符
    if (cmd_len > 0 && cmd_len < sizeof(dma_buffer) - 3)
    {
        memset(dma_buffer + cmd_len, 0xFF, 3); // 追加三个0xFF
        cmd_len += 3;
    }
    else
    {
        return; // 缓冲区溢出保护
    }

    // 硬件级状态检测
    if (!UART_READY())
        return;

    HAL_UART_Transmit_DMA(&SCREEN_USART_HANDLE, dma_buffer, cmd_len);
}

/// @brief 设置屏幕休眠
/// @param is_sleep 是否休眠
void Set_Screen_Sleep(bool is_sleep)
{
    static uint8_t dma_buffer[16];
    const char *cmd_template = "sleep=%d"; // 优化命令生成方式

    // 生成完整命令（含终止符）
    int cmd_len = snprintf((char *)dma_buffer, sizeof(dma_buffer), cmd_template, is_sleep ? 1 : 0);
    if (cmd_len > 0 && cmd_len < sizeof(dma_buffer) - 3)
    {
        memset(dma_buffer + cmd_len, 0xFF, 3);
        cmd_len += 3;
    }
    else
    {
        return;
    }

    // 硬件状态检查
    if (!UART_READY())
        return;

    HAL_UART_Transmit_DMA(&SCREEN_USART_HANDLE, dma_buffer, cmd_len);
}

/*
 * @brief 在当前页面写字
 * @param x 起始点坐标x
 * @param y 起始点坐标y
 * @param w 区域宽度
 * @param h 区域高度
 * @param fontid 字库ID
 * @param point_color 字体颜色
 * @param back_color 背景色
 * @param x_center 水平对齐方式
 * @param y_center 垂直对齐方式
 * @param sta 背景填充方式
 * @param text 字符内容
 */
void Send_Xstr(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
               uint16_t fontid, uint16_t point_color, uint16_t back_color,
               uint8_t x_center, uint8_t y_center, uint8_t sta, char *text)
{
    // 静态缓冲区保证DMA传输期间数据有效
    static uint8_t dma_buffer[128];

    // 生成命令（包含三个终止0xFF）
    int cmd_len = snprintf((char *)dma_buffer, sizeof(dma_buffer),
                           "xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",
                           x, y, w, h, fontid,
                           point_color, back_color, x_center, y_center, sta, text);

    // 手动添加三个0xFF终止符
    if (cmd_len > 0 && (size_t)cmd_len < sizeof(dma_buffer) - 3)
    {
        memset(dma_buffer + cmd_len, 0xFF, 3);
        cmd_len += 3;
    }
    else
    {
        return; // 缓冲区溢出保护
    }

    UART_READY();

    // 启动DMA传输（自动设置BSY标志）
    HAL_UART_Transmit_DMA(&SCREEN_USART_HANDLE, dma_buffer, cmd_len);
}
