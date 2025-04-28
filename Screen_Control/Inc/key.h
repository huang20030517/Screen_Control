#ifndef __KEY_H
#define __KEY_H

#include "config.h"
#include "stm32f4xx_hal.h"

// 按键ID枚举定义
typedef enum
{
    KEY_ID_START = 0, // 开始
    KEY_ID_FOR,       // 进入
    KEY_ID_UP,        // 上
    KEY_ID_SELECT,    // 选择
    KEY_ID_STOP,      // 停止
    KEY_ID_BACK,      // 返回
    KEY_ID_DOWN,      // 下
    KEY_ID_ENTER,     // 确定
    KEY_ID_REMOTE,    // 遥控
    KEY_ID_COUNT      // 按键总数
} KeyID;

// 按键事件类型枚举定义
typedef enum
{
    KEY_EVENT_SHORT_PRESS = 0, // 短按
    KEY_EVENT_LONG_PRESS,      // 长按
    KEY_EVENT_UNKNOWN          // 未知
} KeyEventType;

// 按键事件结构体定义
typedef struct
{
    KeyID key_id;            // 按键ID
    KeyEventType event_type; // 事件类型
    uint32_t timestamp;      // 时间戳（单位：毫秒）
} KeyEvent;

// 初始化按键模块
void Key_Init(void);

// 扫描并返回按键事件
KeyEvent Key_Scan(void);

#endif
