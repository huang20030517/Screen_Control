#include "key.h"

static const struct
{
    KeyID key_id;
    uint16_t gpio_pin;
    GPIO_TypeDef *gpio_port;
} key_config[KEY_ID_COUNT] = {

    {KEY_ID_START, START_PIN, START_GPIO},    // ��ʼ
    {KEY_ID_FOR, FOR_PIN, FOR_GPIO},          // ����
    {KEY_ID_UP, UP_PIN, UP_GPIO},             // ��
    {KEY_ID_SELECT, SELECT_PIN, SELECT_GPIO}, // ѡ��

    {KEY_ID_STOP, STOP_PIN, STOP_GPIO},   // �ر�
    {KEY_ID_BACK, BACK_PIN, BACK_GPIO},   // ����
    {KEY_ID_DOWN, DOWN_PIN, DOWN_GPIO},   // ��
    {KEY_ID_ENTER, ENTER_PIN, ENTER_GPIO}, // ȷ��
	
	{KEY_ID_REMOTE, REMOTE_PIN, REMOTE_GPIO} // Զ�̿���
};

// ����״̬���ٽṹ��
typedef struct
{
    uint8_t last_state;     // ��һ��״̬��0:�ͷ�, 1:���£�
    uint32_t press_time;    // ���¿�ʼʱ��
    uint8_t long_triggered; // �����Ѵ�����־
} KeyState;

static KeyState key_states[KEY_ID_COUNT]; // ���а���״̬

/// @brief ������ʼ��
void Key_Init(void)
{
    memset(key_states, 0, sizeof(key_states));
}


/// @brief ����ɨ��
/// @return �����¼�
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
	
    if (remote_state) // ����Զ�̿���
    {
        event.key_id = KEY_ID_REMOTE; 
        return event; // ����ȥ
    }
	
    // ���ؿ���
    for (int i = 0; i < KEY_ID_COUNT; i++)
    {
        #if LOCAL_ACTIVE == 1
            uint8_t curr_state = (HAL_GPIO_ReadPin(key_config[i].gpio_port,
                                                   key_config[i].gpio_pin) == GPIO_PIN_SET);
        #elif LOCAL_ACTIVE == 2
            uint8_t curr_state = (HAL_GPIO_ReadPin(key_config[i].gpio_port,
                                                   key_config[i].gpio_pin) == GPIO_PIN_RESET);
        #endif

        // ״̬�仯���
        if (curr_state != key_states[i].last_state)
        {
            // ����״̬����¼ʱ��
            key_states[i].last_state = curr_state;
            key_states[i].press_time = HAL_GetTick();

            if (curr_state)
            { 
                // ���¶���
                key_states[i].long_triggered = 0;
            }
            else
            {   
                // �ͷŶ��������ȴ���
                // �ͷ�ʱ���ɶ̰��¼�����δ����������
                if (!key_states[i].long_triggered)
                {
                    event.key_id = key_config[i].key_id;
                    event.event_type = KEY_EVENT_SHORT_PRESS;
                    event.timestamp = HAL_GetTick();
                    return event; // �����¼� ����
                }
            }
        }

        // ������⣨�������³�����ֵ��
        if (curr_state &&
            (HAL_GetTick() - key_states[i].press_time > LONG_PRESS_MS) &&
            !key_states[i].long_triggered)
        {
            key_states[i].long_triggered = 1; // ����Ѵ�������
            event.key_id = key_config[i].key_id;
            event.event_type = KEY_EVENT_LONG_PRESS;
            event.timestamp = HAL_GetTick();
            return event; // �����¼� ����
        }
    }

    return event; // ���¼�ʱ������Ч�¼�
}
