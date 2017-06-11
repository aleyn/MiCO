/******************** Copyright wisearm.com *********************************
* File Name         : CrabUserDebug.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 用户自定义硬件调试任务
********************************************************************************/
#include "CrabVMS.h"
#include "CrabUserDebug.h"

#define LOCAL_UDP_PORT 20000

void CrabUserDebug();
void udp_unicast_thread( void *arg );

/*******************************************************************************
 * Function    : CrabEventTask
 * Caption     : 事件任务
 * Description : .
 *******************************************************************************/
void CrabUserDebugTask()
{  
  CrabTaskSuspend(CRAB_TASK_DEBUG);
  
  while (1)
  {
    Log("Running in DEBUG mode...");
    
    CrabUserDebug( );
    
    CrabTaskSuspend(CRAB_TASK_DEBUG);
  }
}

void CrabUserDebug()
{

}



// END OF FILE