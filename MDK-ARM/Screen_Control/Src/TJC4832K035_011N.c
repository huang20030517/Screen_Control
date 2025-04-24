#include <stdbool.h>

void Screen_Clear(uint16_t color)
{
    printf("sleep=0\xff\xff\xff");
    char command[50];
    snprintf(command, sizeof(command), "cls %d\xff\xff\xff", color);

    HAL_UART_Transmit(&SCREEN_USART_HANDLE, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
}

void Send_Xstr(uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
               uint16_t fontid, uint16_t point_color, uint16_t back_color,
               uint8_t x_center, uint8_t y_center, uint8_t sta, char *text)
{
    printf("sleep=0\xff\xff\xff");
    char command[128];  

    snprintf(command, sizeof(command), 
             "xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s\xff\xff\xff", 
             x, y, w, h, fontid, 
             point_color, back_color, x_center, y_center, sta, text);
    
    HAL_UART_Transmit(&SCREEN_USART_HANDLE, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
}

void ok()
{
    printf("OK\n");
}

void Set_Sleep()
{
    char command[] = "sleep=0\xff\xff\xff";
    HAL_UART_Transmit(&SCREEN_USART_HANDLE, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
}

void Wake_Screen()
{
    char command[] = "sleep=0\xff\xff\xff";
    HAL_UART_Transmit(&SCREEN_USART_HANDLE, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
}

void Sleep_Screen()
{
    char command[] = "sleep=1\xff\xff\xff";
    HAL_UART_Transmit(&SCREEN_USART_HANDLE, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
}

void Set_Screen_Sleep(bool is_sleep)
{
    char command[20];
    if (is_sleep) {
        snprintf(command, sizeof(command), "sleep=1\xff\xff\xff");
    } else {
        snprintf(command, sizeof(command), "sleep=0\xff\xff\xff");
    }
    HAL_UART_Transmit(&SCREEN_USART_HANDLE, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
} 