#include "menu_config.h"

#include <stddef.h>

// ����ģʽ�Ӳ˵���
const MenuItem work_mode_items[] = {
    {"1. �Զ���", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"2. �Զ���", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"3. ������տ���", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"4. ���ѹ������", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"5. ���ſ��ȿ���", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"6. ���ſ��ȱ���", MENU_TYPE_ACTION, NULL, NULL, 0}
};
const uint8_t work_mode_size = sizeof(work_mode_items) / sizeof(MenuItem);

// ���������Ӳ˵���
const MenuItem work_params_items[] = {
    {"1. ѹ����λ����", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"2. ��ѹPID����", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"3. λ�û�PID����", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"4. ����ȫ��ֵ����", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"5. ���У׼", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"6. REMOTE���", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"7. �����¼", MENU_TYPE_ACTION, NULL, NULL, 0}
};
const uint8_t work_params_size = sizeof(work_params_items) / sizeof(MenuItem);

// �����������Ӳ˵���
const MenuItem ctrl_params_items[] = {
    {"1. ��������������", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"2. ������������", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"3. ͨ������", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"4. ��������", MENU_TYPE_SUBMENU, NULL, NULL, 0},
    {"5. �������ź�ƫ��", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"6. ģ��������У׼", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"7. ģ���������ź�ƫ��", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"8. �ָ�Ĭ��", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"9. ������Ĭ��ֵ����", MENU_TYPE_ACTION, NULL, NULL, 0},
    {"10. ���ؼ�����ֵ����", MENU_TYPE_ACTION, NULL, NULL, 0}
};
const uint8_t ctrl_params_size = sizeof(ctrl_params_items) / sizeof(MenuItem);

// ���˵���
const MenuItem main_menu_items[] = {
    {"1. ����ģʽѡ��", MENU_TYPE_SUBMENU, NULL, work_mode_items, sizeof(work_mode_items)/sizeof(MenuItem)},
    {"2. ������������", MENU_TYPE_SUBMENU, NULL, work_params_items, sizeof(work_params_items)/sizeof(MenuItem)},
    {"3. ����������", MENU_TYPE_SUBMENU, NULL, ctrl_params_items, sizeof(ctrl_params_items)/sizeof(MenuItem)}
};
const uint8_t main_menu_size = sizeof(main_menu_items) / sizeof(MenuItem);