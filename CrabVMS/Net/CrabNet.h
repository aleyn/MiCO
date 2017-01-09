/******************** Copyright wisearm.com *********************************
* File Name         : CrabNet.h
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-11-15
* Last Update       : 2017-01-09
* Description       : MiCO Wi-fi Module
********************************************************************************/
#ifndef __CRAB_NET__
#define __CRAB_NET__

#include "CrabVMS.h"
#include "mico.h"

#ifdef  __cplusplus
extern "C" {
#endif  

extern mico_semaphore_t  wait_sem;
extern CrabBool  NetState;
  
void CrabNetInit();

CrabUint GetHostIpByName (CrabAnsi Name, struct in_addr *addr);
  
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE