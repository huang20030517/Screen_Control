#ifndef __STATE_H
#define __STATE_H

#include <stdbool.h>
#include "key.h"

/**
 * @brief 菜单状态枚举
 */
typedef enum
{
    /***************************[ 一级菜单 ]***************************/
    STATE_MAIN, // 主菜单

    /***************************[ 二级菜单 ]***************************/
    //-- 工作模式 --
    STATE_WORK_MODE, // 工作模式选择
    //-- 工作参数 --
    STATE_WORK_PARAMS, // 工作参数设置
    //-- 控制器参数 --
    STATE_CTRL_PARAMS, // 控制器参数设置

    /***************************[ 三级菜单 ]***************************/
    /*---- 工作模式子项 (父级: STATE_WORK_MODE) ----*/
    STATE_WORK_MODE_AUTO_OFF,   // 自动关
    STATE_WORK_MODE_AUTO_ON,    // 自动开
    STATE_WORK_MODE_SLOW_CTRL,  // 慢速真空控制
    STATE_WORK_MODE_REAL_PRESS, // 真空压力控制
    STATE_WORK_MODE_VALVE_OPEN, // 阀门开度控制
    STATE_WORK_MODE_VALVE_HOLD, // 阀门开度保持

    /*---- 工作参数子项 (父级: STATE_WORK_PARAMS) ----*/
    STATE_WORK_PARAM_P_UNIT,      // 压力单位设置
    STATE_WORK_PARAM_PID,         // 控压PID设置
    STATE_WORK_PARAM_POS_PID,     // 位置环PID设置
    STATE_WORK_PARAM_VALVE_CLOSE, // 阀门全关值设置
    STATE_WORK_PARAM_ZERO_CALIB,  // 零点校准
    STATE_WORK_PARAM_REMOTE_CHK,  // REMOTE检查
    STATE_WORK_PARAM_ERR_LOG,     // 错误记录

    /*---- 控制器参数-通信组 (父级: STATE_CTRL_PARAMS) ----*/
    STATE_CTRL_SENSOR_RANGE,     // 传感器量程设置
    STATE_CTRL_INTERLOCK_PARAMS, // 联锁参数设置

    STATE_CTRL_COMM_SETTING,    // 通信设置
    STATE_CTRL_NETWORK_SETTING, // 网口设置

    STATE_CTRL_SENSOR_OFFSET, // 传感器信号偏置

    STATE_CTRL_AI_CALIB,  // 模拟量输入校准
    STATE_CTRL_AI_OFFSET, // 模拟量输入信号偏置

    STATE_CTRL_RESTORE_DEFAULT,        // 恢复默认
    STATE_CTRL_CNT_DEFAULT,            // 控制器默认值设置
    STATE_CTRL_SWITCH_COUNT_THRESHOLD, // 开关计数阀值设置

    /***************************[ 四级菜单 ]***************************/

    /*---- 传感器信号偏置 (父级: STATE_CTRL_SENSOR_OFFSET) ----*/
    STATE_CTRL_SENSOR_P1_OFFSET, // 传感器P1信号偏置
    STATE_CTRL_SENSOR_P2_OFFSET, // 传感器P2信号偏置

    /*-- 通信协议子项 (父级: STATE_CTRL_COMM_SETTING) --*/
    STATE_CTRL_REMOTE_COMM,  // 远程通信方式
    STATE_CTRL_SERIAL_PARAM, // 串行参数

    // 校准子项 (父级: STATE_CTRL_AI_CALIB)
    STATE_CTRL_P1_CALIB,        // P1校准
    STATE_CTRL_P2_CALIB,        // P2校准
    STATE_CTRL_PRESS_CALIB,     // 压力校准
    STATE_CTRL_SPEED_CALIB,     // 抽速校准
    STATE_CTRL_VALVE_POS_CALIB, // 阀门校准

    // 偏置子项 (父级: STATE_CTRL_AI_OFFSET)
    STATE_CTRL_PRESS_REF_OFFSET, // 压力给定信号偏置
    STATE_CTRL_SPEED_REF_OFFSET, // 抽速给定信号偏置
    STATE_CTRL_OPEN_REF_OFFSET,  // 阀门开度给定信号偏置

    /***************************[ 系统状态 ]***************************/
    STATE_ERROR,   // 错误状态
    STATE_EDITING, // 参数编辑

    STATE_COUNT
} MenuState;

typedef struct {
    MenuState current;        // 当前状态
    MenuState prev_states[5]; // 状态堆栈（支持5级返回）
    uint8_t stack_depth;      // 堆栈深度
    int8_t cursor_pos;        // 当前菜单选中项索引
	
	
} MenuContext;




void Handle_Menu_Key(KeyEvent event);


#endif