#ifndef __KEY_H
#define __KEY_H

#include "config.h"
#include "stm32f4xx_hal.h"

// ����ID���빦�ܶ�Ӧ��
typedef enum
{

    KEY_ID_START = 0, // ��ʼ
    KEY_ID_FOR,       // ����
    KEY_ID_UP,        // ��
    KEY_ID_SELECT,    // ѡ��

    KEY_ID_STOP,  // �ر�
    KEY_ID_BACK,  // ����
    KEY_ID_DOWN,  // ��
    KEY_ID_ENTER, // ȷ��
		
	KEY_ID_REMOTE, // Զ�̿���
	
    KEY_ID_COUNT // ��������
} KeyID;

// �����¼����ͣ��̰�/������
typedef enum
{
    KEY_EVENT_SHORT_PRESS = 0, // �̰�
    KEY_EVENT_LONG_PRESS,      // ����
		KEY_EVENT_UNKNOWN      // δ֪
} KeyEventType;

// �����¼��ṹ��
typedef struct
{
    KeyID key_id;            // �ĸ�����
    KeyEventType event_type; // �¼�����
    uint32_t timestamp;      // ʱ�����ms��
} KeyEvent;

// ��ʼ������ģ��
void Key_Init(void);

// ɨ�谴���������¼�
KeyEvent Key_Scan(void);

#endif
	