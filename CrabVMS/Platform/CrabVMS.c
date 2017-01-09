/******************** Copyright wisearm.com *********************************
* File Name         : CrabVMS.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 主程序入口
********************************************************************************/
#include "mico.h"
#include "CrabVMS.h"

int application_start( void )
{
  //初始化MiCO
  mico_system_init( mico_system_context_init( 0 ) );  
    
  //初始化硬件
  Hardware_Init();
  
  //初始化网络
  CrabNetInit();
  
  //运行虚拟机
  CrabSystem_Running();
 
  return 0;
}
