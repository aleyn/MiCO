/******************** Copyright wisearm.com *********************************
* File Name         : CrabVMS.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ���������
********************************************************************************/
#include "CrabVMS.h"
#include "mico.h"

int application_start( void )
{
  //��ʼ��MiCO
  mico_system_init( mico_system_context_init( 0 ) );  
    
  //��ʼ��Ӳ��
  Hardware_Init();
  
  //��ʼ������
  CrabNetInit();
  
  //���������
  CrabSystem_Running();
 
  return 0;
}
