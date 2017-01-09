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
CrabBool  NetState = CrabFalse;

static void micoNotify_ApListCallback(ScanResult *pApList);
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
static void micoNotify_ApListCallback(ScanResult *pApList)
{
  int i=0;
  for(i=0; i<pApList->ApNum; i++)
  {
    Log("%6d: %s [%d%%];", i+1, pApList->ApList[i].ssid, pApList->ApList[i].ApPower);
    //CrabDelay(1);
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
// END OF FILE