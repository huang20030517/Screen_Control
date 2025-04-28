#include "key.h"

static const struct
{
    KeyID key_id;
    uint16_t gpio_pin;
    GPIO_TypeDef *gpio_port;
} key_config[KEY_ID_COUNT] = {

    {KEY_ID_START, START_PIN, START_GPIO},    // 开始
    {KEY_ID_FOR, FOR_PIN, FOR_GPIO},          // 进入
    {KEY_ID_UP, UP_PIN, UP_GPIO},             // 上
    {KEY_ID_SELECT, SELECT_PIN, SELECT_GPIO}, // 选择

    {KEY_ID_STOP, STOP_PIN, STOP_GPIO},   // 关闭
    {KEY_ID_BACK, BACK_PIN, BACK_GPIO},   // 返回
    {KEY_ID_DOWN, DOWN_PIN, DOWN_GPIO},   // 下
    {KEY_ID_ENTER, ENTER_PIN, ENTER_GPIO}, // 确认
	
	{KEY_ID_REMOTE, REMOTE_PIN, REMOTE_GPIO} // 远程控制
};

// 按键状态跟踪结构体
typedef struct
{
    uint8_t last_state;     // 上一次状态（0:释放, 1:按下）
    uint32_t press_time;    // 按下开始时间
    uint8_t long_triggered; // 长按已触发标志
} KeyState;

static KeyState key_states[KEY_ID_COUNT]; // 所有按键状态

/// @brief 按键初始化
void Key_Init(void)
{
    memset(key_states, 0, sizeof(key_states));
}


/// @brief 按键扫描
/// @return 按键事件
KeyEvent Key_Scan(void)
{
    
	KeyEvent event = {.key_id = KEY_ID_COUNT, 
					  .event_type = KEY_EVENT_UNKNOWN,
					  .timestamp = 0};	

	#if REMOTE_ACTIVE == 1
        uint8_t remote_state = (HAL_GPIO_ReadPin(key_config[KEY_ID_REMOTE].gpio_port,
                                                   key_config[KEY_ID_REMOTE].gpio_pin) == GPIO_PIN_SET);
    #elif REMOTE_ACTIVE == 2
        uint8_t remote_state = (HAL_GPIO_ReadPin(key_config[KEY_ID_REMOTE].gpio_port,
                                                   key_config[KEY_ID_REMOTE].gpio_pin) == GPIO_PIN_RESET);
    #endif
	
    if (remote_state) // 开启远程控制
    {
        event.key_id = KEY_ID_REMOTE; 
        return event; // 滚出去
    }
	
    // 本地控制
    for (int i = 0; i < KEY_ID_COUNT; i++)
    {
        #if LOCAL_ACTIVE == 1
            uint8_t curr_state = (HAL_GPIO_ReadPin(key_config[i].gpio_port,
                                                   key_config[i].gpio_pin) == GPIO_PIN_SET);
        #elif LOCAL_ACTIVE == 2
            uint8_t curr_state = (HAL_GPIO_ReadPin(key_config[i].gpio_port,
                                                   key_config[i].gpio_pin) == GPIO_PIN_RESET);
        #endif

        // 状态变化检测
        if (curr_state != key_states[i].last_state)
        {
            // 更新状态并记录时间
            key_states[i].last_state = curr_state;
            key_states[i].press_time = HAL_GetTick();

            if (curr_state)
            { 
                // 按下动作
                key_states[i].long_triggered = 0;
            }
            else
            {   
                // 释放动作（优先处理）
                // 释放时生成短按事件（若未触发长按）
                if (!key_states[i].long_triggered)
                {
                    event.key_id = key_config[i].key_id;
                    event.event_type = KEY_EVENT_SHORT_PRESS;
                    event.timestamp = HAL_GetTick();
                    return event; // 返回事件 滚蛋
                }
            }
        }

        // 长按检测（持续按下超过阈值）
        if (curr_state &&
            (HAL_GetTick() - key_states[i].press_time > LONG_PRESS_MS) &&
            !key_states[i].long_triggered)
        {
            key_states[i].long_triggered = 1; // 标记已触发长按
            event.key_id = key_config[i].key_id;
            event.event_type = KEY_EVENT_LONG_PRESS;
            event.timestamp = HAL_GetTick();
            return event; // 返回事件 滚蛋
        }
    }

    return event; // 无事件时返回无效事件
}
