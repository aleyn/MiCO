/******************** Copyright wisearm.com *********************************
* File Name         : CrabEvent.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 事件管理器
********************************************************************************/
#include "CrabVMS.h"
#include "CrabEvent.h"

extern uint16_t BoardKey;
/*******************************************************************************
 * Function    : CrabEventTask
 * Caption     : 事件任务
 * Description : .
 *******************************************************************************/
void CrabEventTask()
{ 
  CrabUint Key;
  
  CrabTaskSuspend(CRAB_TASK_EVENT);
  
  while (1)
  {
  #if KEY_BUFFER_MODE == 1
    CrabHW_KEY_Scan();
    Key = CrabHW_KEY_Read();
  #else
    Key = CrabHW_KEY_Scan();
  #endif
    if (Key)
    {
      BoardKey = Key;
    #if KEY_DETAIL == 1
      CrabFifo_PushEvent(KEY_PRESS | Key);
    #else
      CrabFifo_PushEvent(KEY_PRESS);
    #endif
    }
    
    CrabDelay(10);
  }
}
  


// END OF FILE