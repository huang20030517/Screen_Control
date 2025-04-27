#ifndef __KEY_H
#define __KEY_H

#include "config.h"
#include "stm32f4xx_hal.h"

// 按键ID（与功能对应）
typedef enum
{

    KEY_ID_START = 0, // 开始
    KEY_ID_FOR,       // 进入
    KEY_ID_UP,        // 上
    KEY_ID_SELECT,    // 选择

    KEY_ID_STOP,  // 关闭
    KEY_ID_BACK,  // 返回
    KEY_ID_DOWN,  // 下
    KEY_ID_ENTER, // 确认
		
	KEY_ID_REMOTE, // 远程控制
	
    KEY_ID_COUNT // 按键总数
} KeyID;

// 按键事件类型（短按/长按）
typedef enum
{
    KEY_EVENT_SHORT_PRESS = 0, // 短按
    KEY_EVENT_LONG_PRESS,      // 长按
		KEY_EVENT_UNKNOWN      // 未知
} KeyEventType;

// 按键事件结构体
typedef struct
{
    KeyID key_id;            // 哪个按键
    KeyEventType event_type; // 事件类型
    uint32_t timestamp;      // 时间戳（ms）
} KeyEvent;

// 初始化按键模块
void Key_Init(void);

// 扫描按键并返回事件
KeyEvent Key_Scan(void);

#endif
	