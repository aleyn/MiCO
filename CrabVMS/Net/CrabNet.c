/******************** Copyright wisearm.com *********************************
* File Name         : CrabNet.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-11-15
* Last Update       : 2017-01-09
* Description       : MiCO Wi-fi Module
********************************************************************************/

#include "CrabVMS.h"
#include "CrabNet.h"
#include "common.h"
#include "platform_peripheral.h"
#include "mico_platform.h"
#include "json_c/json.h"

mico_semaphore_t  wait_sem = NULL;
CrabBool          NetState = CrabFalse;
CrabString       *ApList;
CrabUint          UdpUnicastPort = 0;
CrabString        UdpSendStr;
CrabString        UdpRecvStr;
CrabString        UdpRemoteIP;
CrabUint          UdpRemotePort = 0;

TASK_HANDLE 	CrabUdpUnicast_Task_Object;

static void micoNotify_ApListCallback(ScanResult *pApList, void * inContext);
static void micoNotify_ApListAdvCallback(ScanResult_adv *pApList, void * inContext);
static void micoNotify_ConnectFailedHandler(OSStatus err, void* inContext);
static void micoNotify_WifiStatusHandler(WiFiEvent event,  void* inContext);

/*******************************************************************************
 * Function    : CrabNetInit
 * Caption     : 网络初始化
 * Description : .
 *******************************************************************************/
void CrabNetInit()
{
  OSStatus err = kNoErr;
  
  NetState = CrabFalse;
  
  /* Register user function when wlan scan is completed */
  err = mico_system_notify_register( mico_notify_WIFI_SCAN_COMPLETED, (void *)micoNotify_ApListCallback, NULL );  
  require_noerr( err, exit ); 
  
  err = mico_system_notify_register( mico_notify_WIFI_SCAN_ADV_COMPLETED, (void *)micoNotify_ApListAdvCallback, NULL );  
  require_noerr( err, exit ); 
  
  
  /* Register user function when wlan connection status is changed */
  err = mico_system_notify_register( mico_notify_WIFI_STATUS_CHANGED, (void *)micoNotify_WifiStatusHandler, NULL );
  require_noerr( err, exit ); 
  
  /* Register user function when wlan connection is faile in one attempt */
  err = mico_system_notify_register( mico_notify_WIFI_CONNECT_FAILED, (void *)micoNotify_ConnectFailedHandler, NULL );
  require_noerr( err, exit ); 
  
  exit:  
    return;
}

/*******************************************************************************
 * Function    : micoNotify_ApListCallback
 * Caption     : 路由器搜索回调函数
 * Description : .
 *******************************************************************************/
static void micoNotify_ApListCallback(ScanResult *pApList, void * inContext)
{
  int I;
  
  //CrabExtern_CreateArrayAsString(ApList, pApList->ApNum); 
    
  /*for(I=0; I<pApList->ApNum; I++)
  {
    L = CrabAnsiStrLen(pApList->ApList[I].ssid, 32);
    ApList[I] = CrabStringCreateFromAnsi(pApList->ApList[I].ssid, L);  //这段程序有问题
  }*/

  for(I=0; I<pApList->ApNum; I++)
  {
    Log("%6d: %s [%d%%];", I+1, pApList->ApList[I].ssid, pApList->ApList[I].ApPower);
    CrabDelay(50);
  }
  
  Log("Total %d WIFI AP;", pApList->ApNum);
  //mico_rtos_set_semaphore( &wait_sem );
}

static void micoNotify_ApListAdvCallback(ScanResult_adv *pApList, void * inContext)
{
  int I;
  
  for(I=1; I<pApList->ApNum; I++)
  {
    Log("%6d: %s [%d%%];", I+1, pApList->ApList[I].ssid, pApList->ApList[I].ApPower);
    CrabDelay(50);
  }
  
  Log("Total %d WIFI AP;", pApList->ApNum);
  mico_rtos_set_semaphore( &wait_sem );
}

/*******************************************************************************
 * Function    : micoNotify_ConnectFailedHandler
 * Caption     : 路由器连接失败回调函数
 * Description : .
 *******************************************************************************/
static void micoNotify_ConnectFailedHandler(OSStatus err, void* inContext)
{
  Log("join Wlan failed Err: %d", err);
}

/*******************************************************************************
 * Function    : micoNotify_WifiStatusHandler
 * Caption     : 路由器状态回调函数
 * Description : .
 *******************************************************************************/
static void micoNotify_WifiStatusHandler(WiFiEvent event,  void* inContext)
{
  switch (event) 
  {
  case NOTIFY_STATION_UP:
  {
    mico_rtos_set_semaphore( &wait_sem );
    NetState = CrabTrue;
    //Log("Station up");
    break;
  }
  case NOTIFY_STATION_DOWN:
  {
    NetState = CrabFalse;
    //Log("Station down");
    break;
  }
  default:
    break;
  }
}

/*******************************************************************************
 * Function    : GetHostIpByName
 * Caption     : 通过域名获取IP地址
 * Description : .
 *******************************************************************************/
CrabUint GetHostIpByName (CrabAnsi Name, struct in_addr *addr)
{
  char **pptr = NULL;
  struct hostent* host = NULL;

  if (!NetState)
  {
    return 0;
  }
  
  host = gethostbyname( Name );
  
  if (host != NULL)
  {
    pptr = host->h_addr_list;
    
    if (*pptr != NULL)
    {
      addr->s_addr = *(uint32_t *)(*pptr);
      return addr->s_addr;
    }
  }
  
  return 0;
}

/*******************************************************************************
 * Function    : CrabUdpUnicast_Task
 * Caption     : UDP单播任务
 * Description : .
 *******************************************************************************/
void CrabUdpUnicast_Task( void *arg )
{
    UNUSED_PARAMETER( arg );

    OSStatus err;
    struct sockaddr_in addr;
    fd_set readfds;
    socklen_t addrLen = sizeof(addr);
    int udp_fd = -1, len;
    //char ip_address[16];
    
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 100;
    UdpSendStr = CrabStringAlloc(255);
    UdpRecvStr = CrabStringAlloc(255);
    UdpRemoteIP = CrabStringAlloc(20);
    
    /*Establish a UDP port to receive any data sent to this port*/
    udp_fd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    require_action( IsValidSocket( udp_fd ), exit, err = kNoResourcesErr );

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(UdpUnicastPort);
    err = bind( udp_fd, (struct sockaddr *)&addr, sizeof(addr) );
    require_noerr( err, exit );
    
    //Log("Open local UDP port %d", UdpUnicastPort);

    while ( 1 )
    {
        if (UdpUnicastPort == 0) 
        {
          break;
        }
        
        FD_ZERO( &readfds );
        FD_SET( udp_fd, &readfds );

        require_action( select(udp_fd + 1, &readfds, NULL, NULL, &timeout) >= 0, exit,
                        err = kConnectionErr );

        /*Read data from udp and send data back */
        if ( FD_ISSET( udp_fd, &readfds ) )
        {
            len = recvfrom( udp_fd, UdpRecvStr->Data, UdpRecvStr->Size, 0, (struct sockaddr *)&addr, &addrLen );
            
            if (len)
            {
              UdpRecvStr->Len = len;
              
              CrabStringClear(UdpRemoteIP);
              strcpy(UdpRemoteIP->Data, inet_ntoa(addr.sin_addr));
              UdpRemoteIP->Len = strlen(UdpRemoteIP->Data);
              UdpRemotePort = htons(addr.sin_port);
              
              CrabFifo_PushEvent(NET_UDP_RECEIVE);

              //strcpy(ip_address, inet_ntoa(addr.sin_addr));
              //Log( "udp recv from %s:%d, len:%d", ip_address, htons(addr.sin_port), len );
            }
           
            //vTaskSuspend(CrabUdpUnicast_Task_Object);            
        }

        if (UdpSendStr->Len > 0)
        {
          sendto( udp_fd, UdpSendStr->Data, UdpSendStr->Len, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in) );
          UdpSendStr->Len = 0;
        }
    }

    close(udp_fd);
    //Log("Close UDP port.");
    
    exit:
    //if ( err != kNoErr )
    //    Log("UDP thread exit with err: %d", err);
    
    CrabStringFree(UdpSendStr);
    CrabStringFree(UdpRecvStr);
    CrabStringFree(UdpRemoteIP);
    
    UdpRemotePort  = 0;
    
    mico_rtos_delete_thread( NULL );
}

/*******************************************************************************
 * Function    : CrabUdpUnicast_Cmd
 * Caption     : UDP单播任务命令
 * Description : .
 *******************************************************************************/
void CrabUdpUnicast_Cmd(CrabByte Cmd)
{
  switch (Cmd)
  {
    case CrabUdpUnicast_Cmd_Create:
    {    
      xTaskCreate(CrabUdpUnicast_Task,
                  CrabUdpUnicast_Task_Name,
                  CrabUdpUnicast_Task_Size,
                  CrabUdpUnicast_Task_Param,
                  CrabUdpUnicast_Task_Level,
                 &CrabUdpUnicast_Task_Object);
      break;
    }
    case CrabUdpUnicast_Cmd_Free:
    {
      //vTaskDelete( CrabUdpUnicast_Task_Object );
      CrabUdpUnicast_Task_Object = null;
      break;
    }
    case CrabUdpUnicast_Cmd_Suspend:
    {
      vTaskSuspend(CrabUdpUnicast_Task_Object);
      break;
    }
    case CrabUdpUnicast_Cmd_Resume:
    {
      vTaskResume(CrabUdpUnicast_Task_Object);
      break;
    }
  }
}

/*******************************************************************************
 * Function    : CrabUdpUnicast_Status
 * Caption     : 获取UDP单播状态
 * Description : .
 *******************************************************************************/
CrabBool CrabUdpUnicast_Status()
{
  return (CrabUdpUnicast_Task_Object != null);
}
// END OF FILE