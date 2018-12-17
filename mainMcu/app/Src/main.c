/*
 * @Author: zhoumin 
 * @Date: 2018-10-12 14:17:00 
 * @Last Modified by: zhoumin
 * @Last Modified time: 2018-11-08 09:59:39
 */
#include "includes.h"
#include "BswSrv.h"
#include "BswDrv.h"
#include "APP.h"
#include "App_Main.h"
#include "BswSrv_ComTask.h"
#include "BswSrv_NFCard_Task.h"
#include "BswSrv_NetTask.h"
#include "BswSrv_WifiBlueTask.h"


#define VECT_TAB_OFFSET  BOOT_SIZE	//�ж�������ƫ�Ƶ�ַ


//��ʼ����������
void start_task(void *pvParameters)
{
	xTaskCreate((TaskFunction_t)App_MainTask,   "MainTask", 	300, NULL, 3, NULL);
	xTaskCreate((TaskFunction_t)SurfNet_Task,   "SurfNet_Task", 600, NULL, 3, NULL);
	xTaskCreate((TaskFunction_t)NFCardTask,	    "NFCardTask",	256, NULL, 4, NULL);   
	xTaskCreate((TaskFunction_t)WifiBlueTask,	"BlueTask", 	600, NULL, 2, NULL);
	xTaskCreate((TaskFunction_t)ComTask,		"ComTask", 	    384, NULL, 4, NULL);
	
	vTaskDelete(NULL);
}


int main(void)
{	
	/* �����ж�������ƫ�Ƶ�ַ */
	nvic_vector_table_set(NVIC_VECTTAB_FLASH,VECT_TAB_OFFSET);
	
	/*�������ʼ��*/
	BswDrv_Init();
	
	/*������ʼ��*/
	BswSrv_Init();
	
	/*Ӧ�ò��ʼ��*/
	APP_Init();

	//������ʼ����
	xTaskCreate((TaskFunction_t)start_task, "start_task", 128, NULL, 1, NULL);  

	vTaskStartScheduler();          //�����������

	for(;;);
}




