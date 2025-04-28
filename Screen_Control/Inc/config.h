#ifndef __CONFIG_H
#define __CONFIG_H

#include "main.h"

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"

//-------------------------------- 屏幕配置 --------------------------------

#define SCREEN_USART_HANDLE huart3
#define SCREEN_SLEEP_MS  5000  // 熄屏时间(单位为毫秒)

//-------------------------------- 按键配置 --------------------------------

// 按键GPIO配置
#define STOP_GPIO       GPIOD  // 停止按键
#define BACK_GPIO       GPIOD  // 返回按键
#define UP_GPIO         GPIOD  // 上键
#define DOWN_GPIO       GPIOD  // 下键
#define FOR_GPIO        GPIOD  // 前键
#define ENTER_GPIO      GPIOD  // 确认键
#define SELECT_GPIO     GPIOD  // 选择键
#define START_GPIO      GPIOD  // 开始键
#define REMOTE_GPIO     GPIOE	// 远程开关

// 按键引脚配置
#define STOP_PIN      	STOP_BUT_Pin    // 停止按键
#define BACK_PIN        BACK_BUT_Pin    // 返回按键
#define UP_PIN          UP_BUT_Pin      // 上键
#define DOWN_PIN        DOWN_BUT_Pin    // 下键
#define FOR_PIN         FOR_BUT_Pin     // 前键
#define ENTER_PIN       ENTER_BUT_Pin   // 确认键
#define SELECT_PIN      SELECT_BUT_Pin  // 选择键
#define START_PIN       START_BUT_Pin   // 开始键
#define REMOTE_PIN      GPIO_PIN_11     // 远程开关

// 按键电平配置(1: 高电平有效, 2: 低电平有效)
#define LOCAL_ACTIVE  2   // 本地 
#define REMOTE_ACTIVE 2   // 远程

// 按键长按时间配置(单位为毫秒)
#define LONG_PRESS_MS 1000  



#endif
