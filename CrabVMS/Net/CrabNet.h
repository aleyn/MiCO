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

#define  NET_COMMAND      0x10000000
#define  NET_TCP_MESSAGE  (NET_COMMAND + 0x00100000)
#define  NET_UDP_MESSAGE  (NET_COMMAND + 0x00200000)
#define  NET_UDP_SEND     (NET_UDP_MESSAGE + 0x00010000)
#define  NET_UDP_RECEIVE  (NET_UDP_MESSAGE + 0x00020000)

#define CrabUdpUnicast_Task_Name            (TASK_NAME)"UdpUnicast"
#define CrabUdpUnicast_Task_Level           TASK_PRIO(7)
#define CrabUdpUnicast_Task_Size            256
#define CrabUdpUnicast_Task_Param           NULL

#define CrabUdpUnicast_Cmd_Create           1
#define CrabUdpUnicast_Cmd_Free             2
#define CrabUdpUnicast_Cmd_Suspend          3
#define CrabUdpUnicast_Cmd_Resume           4
  
extern mico_semaphore_t  wait_sem;
extern CrabBool          NetState;
extern CrabString       *ApList;
extern CrabUint          UdpUnicastPort;
extern CrabString        UdpSendStr;
extern CrabString        UdpRecvStr;
extern CrabString        UdpRemoteIP;
extern CrabUint          UdpRemotePort;

void CrabNetInit();
void CrabUdpUnicast_Task( void *arg );

void CrabUdpUnicast_Cmd(CrabByte Cmd);

CrabBool CrabUdpUnicast_Status();

CrabUint GetHostIpByName (CrabAnsi Name, struct in_addr *addr);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE