/*
 * @Author: Huang
 * @Date: 2025-04-23 15:30:00
 * @LastEditTime: 2025-04-23 15:30:00
 * @FilePath: \Screen_Control\Src\TJC4832K035_011N.c
 * @Description:
 * ��д��ĻAPI
 * 480*320�޴�����ϵ�� k0��
 */
#include "TJC4832K035_011N.h"

/* DMA����״̬���꣨Ӳ����ԭ�Ӳ����� */
#define UART_READY() (__HAL_UART_GET_FLAG(&SCREEN_USART_HANDLE, UART_FLAG_TC) != RESET)

/**
 * @brief ����
 * @param color ��ɫ
 */
void Screen_Clear(uint16_t color)
{
    static uint8_t dma_buffer[20]; // ��̬����������DMA���ݰ�ȫ

    // ���ɻ������������ֹ����
    int cmd_len = snprintf((char *)dma_buffer, sizeof(dma_buffer), "cls %d", color);

    // ��ȫ�����ֹ��
    if (cmd_len > 0 && cmd_len < sizeof(dma_buffer) - 3)
    {
        memset(dma_buffer + cmd_len, 0xFF, 3); // ׷������0xFF
        cmd_len += 3;
    }
    else
    {
        return; // �������������
    }

    // Ӳ����״̬���
    if (!UART_READY())
        return;

    HAL_UART_Transmit_DMA(&SCREEN_USART_HANDLE, dma_buffer, cmd_len);

    // �ȴ� DMA �������
    while (__HAL_UART_GET_FLAG(&SCREEN_USART_HANDLE, UART_FLAG_TC) == RESET)
    {
        // �ȴ��������
    }
}

/// @brief ������Ļ����
/// @param is_sleep �Ƿ�����(1 - ˯��, 0 - ��)
void Set_Screen_Sleep(bool is_sleep)
{
    static uint8_t dma_buffer[16];
    const char *cmd_template = "sleep=%d"; // �Ż��������ɷ�ʽ

    // ���������������ֹ����
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

    // Ӳ��״̬���
    if (!UART_READY())
        return;

    HAL_UART_Transmit_DMA(&SCREEN_USART_HANDLE, dma_buffer, cmd_len);

    // �ȴ� DMA �������
    while (__HAL_UART_GET_FLAG(&SCREEN_USART_HANDLE, UART_FLAG_TC) == RESET)
    {
        // �ȴ��������
    }
}

/*
 * @brief �ڵ�ǰҳ��д��
 * @param x ��ʼ������x
 * @param y ��ʼ������y
 * @param w ������
 * @param h ����߶�
 * @param fontid �ֿ�ID
 * @param point_color ������ɫ
 * @param back_color ����ɫ
 * @param xcenter:ˮƽ���뷽ʽ(0Ϊ����룬1Ϊ���У�2Ϊ�Ҷ���)��
 * @param ycenter ��ֱ���뷽ʽ(0Ϊ�϶��룬1Ϊ���У�2Ϊ�¶���)��
 * @param sta ������䷽ʽ(0Ϊ��ͼ��1Ϊ��ɫ��2ΪͼƬ��3Ϊ�ޱ���,sta����Ϊ��ͼ��ͼƬʱ��backcolor��ʾͼƬID)
 * @param text �ַ�����
 */
void Send_Xstr(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
               uint16_t fontid, uint16_t point_color, uint16_t back_color,
               uint8_t x_center, uint8_t y_center, uint8_t sta, char *text)
{
    // ��̬��������֤DMA�����ڼ�������Ч
    static uint8_t dma_buffer[128];

    // �����������������ֹ0xFF��
    int cmd_len = snprintf((char *)dma_buffer, sizeof(dma_buffer),
                           "xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",
                           x, y, w, h, fontid,
                           point_color, back_color, x_center, y_center, sta, text);

    // ���������Ƿ���Ч
    if (cmd_len <= 0 || (size_t)cmd_len >= sizeof(dma_buffer) - 3)
    {
        return; // �������������
    }

    // �ֶ��������0xFF��ֹ��
    memset(dma_buffer + cmd_len, 0xFF, 3);
    cmd_len += 3;

    // ȷ�� UART ׼������
    UART_READY();

    // ���� DMA ���䣨�Զ����� BSY ��־��
    HAL_UART_Transmit_DMA(&SCREEN_USART_HANDLE, dma_buffer, cmd_len);

    // �ȴ� DMA �������
    while (__HAL_UART_GET_FLAG(&SCREEN_USART_HANDLE, UART_FLAG_TC) == RESET)
    {
        // �ȴ��������
    }
}
