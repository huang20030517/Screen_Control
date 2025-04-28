#ifndef __KEY_H
#define __KEY_H

#include "config.h"
#include "stm32f4xx_hal.h"

// ����IDö�ٶ���
typedef enum
{
    KEY_ID_START = 0, // ��ʼ
    KEY_ID_FOR,       // ����
    KEY_ID_UP,        // ��
    KEY_ID_SELECT,    // ѡ��
    KEY_ID_STOP,      // ֹͣ
    KEY_ID_BACK,      // ����
    KEY_ID_DOWN,      // ��
    KEY_ID_ENTER,     // ȷ��
    KEY_ID_REMOTE,    // ң��
    KEY_ID_COUNT      // ��������
} KeyID;

// �����¼�����ö�ٶ���
typedef enum
{
    KEY_EVENT_SHORT_PRESS = 0, // �̰�
    KEY_EVENT_LONG_PRESS,      // ����
    KEY_EVENT_UNKNOWN          // δ֪
} KeyEventType;

// �����¼��ṹ�嶨��
typedef struct
{
    KeyID key_id;            // ����ID
    KeyEventType event_type; // �¼�����
    uint32_t timestamp;      // ʱ�������λ�����룩
} KeyEvent;

// ��ʼ������ģ��
void Key_Init(void);

// ɨ�貢���ذ����¼�
KeyEvent Key_Scan(void);

#endif
