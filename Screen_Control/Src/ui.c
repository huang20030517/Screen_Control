#include "ui.h"


void UI_Init(void)
{
	Key_Init();
	
}


void UI_Task(void)
{
	
	KeyEvent event = Key_Scan(); // ��ȡ�����¼�
       
	Handle_Menu_Key(event);
	
	HAL_Delay(20);
	
}