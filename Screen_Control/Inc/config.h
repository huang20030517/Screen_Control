#ifndef __CONFIG_H
#define __CONFIG_H

#include "main.h"

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"

//-------------------------------- ��Ļ���� --------------------------------

#define SCREEN_USART_HANDLE huart3
#define SCREEN_SLEEP_MS  5000  // Ϩ��ʱ��(��λΪ����)

//-------------------------------- �������� --------------------------------

// ����GPIO����
#define STOP_GPIO       GPIOD  // ֹͣ����
#define BACK_GPIO       GPIOD  // ���ذ���
#define UP_GPIO         GPIOD  // �ϼ�
#define DOWN_GPIO       GPIOD  // �¼�
#define FOR_GPIO        GPIOD  // ǰ��
#define ENTER_GPIO      GPIOD  // ȷ�ϼ�
#define SELECT_GPIO     GPIOD  // ѡ���
#define START_GPIO      GPIOD  // ��ʼ��
#define REMOTE_GPIO     GPIOE	// Զ�̿���

// ������������
#define STOP_PIN      	STOP_BUT_Pin    // ֹͣ����
#define BACK_PIN        BACK_BUT_Pin    // ���ذ���
#define UP_PIN          UP_BUT_Pin      // �ϼ�
#define DOWN_PIN        DOWN_BUT_Pin    // �¼�
#define FOR_PIN         FOR_BUT_Pin     // ǰ��
#define ENTER_PIN       ENTER_BUT_Pin   // ȷ�ϼ�
#define SELECT_PIN      SELECT_BUT_Pin  // ѡ���
#define START_PIN       START_BUT_Pin   // ��ʼ��
#define REMOTE_PIN      GPIO_PIN_11     // Զ�̿���

// ������ƽ����(1: �ߵ�ƽ��Ч, 2: �͵�ƽ��Ч)
#define LOCAL_ACTIVE  2   // ���� 
#define REMOTE_ACTIVE 2   // Զ��

// ��������ʱ������(��λΪ����)
#define LONG_PRESS_MS 1000  



#endif
