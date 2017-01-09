/******************** Copyright wisearm.com *********************************
* File Name         : CrabMicoApi.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2016-06-15
* Last Update       : 2017-01-09
* Description       : API for MICO
********************************************************************************/
#include "CrabVMS.h"
#include "CrabNet.h"
#include <time.h>
#include "mico.h"
#include "common.h"
#include "platform_peripheral.h"
#include "mico_platform.h"
#include "json_c/json.h"
#include "sntp.h"

crabapi CrabApiNetScan        ();
crabapi CrabApiNetConnect     ();
crabapi CrabApiNetGetDns      ();
crabapi CrabApiNetGetLocalIP  ();
crabapi CrabApiNetGetServerDate ();
crabapi CrabApiNetGetServerTime ();

/*******************************************************************************
* Function    : CrabRegisterMicoApi
* Caption     : ע��MiCOר��API����
* Description : .
*******************************************************************************/
void CrabRegisterMicoApi()
{  
  CrabExtern_RegisterApi("NetScan", CrabApiNetScan);
  CrabExtern_RegisterApi("NetConnect", CrabApiNetConnect);
  CrabExtern_RegisterApi("NetGetDns", CrabApiNetGetDns);
  CrabExtern_RegisterApi("NetLocalIP", CrabApiNetGetLocalIP);
  CrabExtern_RegisterApi("NetGetDns", CrabApiNetGetDns);
  CrabExtern_RegisterApi("NetServerDate", CrabApiNetGetServerDate);
  CrabExtern_RegisterApi("NetServerTime", CrabApiNetGetServerTime);
}

/*******************************************************************************
* Function    : CrabApiNetScan
* Caption     : ɨ��WIFI·����
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetScan ()
{
  Log("start scan mode, please wait...");
  mico_rtos_init_semaphore( &wait_sem, 1 );
  micoWlanStartScan( );
  mico_rtos_get_semaphore( &wait_sem, MICO_WAIT_FOREVER );
  if ( wait_sem != NULL )
  {
    mico_rtos_deinit_semaphore( &wait_sem );
  }
}

/*******************************************************************************
* Function    : CrabApiNetConnect
* Caption     : ���ӵ�WIFI·����
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetConnect ()
{     
  network_InitTypeDef_adv_st  wNetConfigAdv;
  IPStatusTypedef para;

  CrabString TmpStr;
  
  /* Initialize wlan parameters */
  memset( &wNetConfigAdv, 0x0, sizeof(wNetConfigAdv) );
  
  TmpStr = CrabExtern_GetStringParam(1);
  strncpy((char*)wNetConfigAdv.ap_info.ssid, TmpStr->Data, TmpStr->Len);       /* wlan ssid string */
  
  TmpStr = CrabExtern_GetStringParam(2);
  strncpy((char*)wNetConfigAdv.key, TmpStr->Data, TmpStr->Len);
    
  wNetConfigAdv.key_len = TmpStr->Len;                          /* wlan key length */
  wNetConfigAdv.ap_info.security = SECURITY_TYPE_AUTO;          /* wlan security mode */
  wNetConfigAdv.ap_info.channel = 0;                            /* Select channel automatically */
  wNetConfigAdv.dhcpMode = DHCP_Client;                         /* Fetch Ip address from DHCP server */
  wNetConfigAdv.wifi_retry_interval = 100;                      /* Retry interval after a failure connection */
  
  mico_rtos_init_semaphore( &wait_sem, 1 );
  
  /* Connect Now! */
  Log("connecting to %s...", wNetConfigAdv.ap_info.ssid);  
  micoWlanStartAdv(&wNetConfigAdv);
  mico_rtos_get_semaphore( &wait_sem, MICO_WAIT_FOREVER );

  if (NetState)
  {
    micoWlanGetIPStatus( &para, Station );
    Log( "WI-FI connected, Local ip address: %s", para.ip );
  }
  else
  {
    Log("WI-FI connect faild" );
  }
  
  if ( wait_sem != NULL )
  {
    mico_rtos_deinit_semaphore( &wait_sem );
  }
}

/*******************************************************************************
* Function    : CrabApiNetGetDns
* Caption     : ��ȡ����DNS��ַ
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetDns ()
{
  struct in_addr addr;
  CrabString TmpStr;
  CrabString Result;
  
  Result = CrabExtern_GetReturnString();
  CrabStringClear(Result);

  if (CrabExtern_ParamIsString(1))
  {  
    TmpStr = CrabExtern_GetStringParam(1);
  }
  else
  {
    Log("Invaild Param.");
    CrabExtern_ReturnNullValue();
    return;
  }
  
  if (!NetState)
  {
    Log("Please Connect to WI-FI");
    CrabExtern_ReturnNullValue();
    return;
  }    
  
  if (GetHostIpByName( TmpStr->Data, &addr))
  {
    CrabStringAssignAnsi(Result, inet_ntoa(addr));
  };

}

/*******************************************************************************
* Function    : CrabApiNetGetLocalIP
* Caption     : ��ȡ����IP��ַ
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetLocalIP ()
{
  IPStatusTypedef para;
  CrabString Result;
  
  Result = CrabExtern_GetReturnString();
  CrabStringClear(Result);
  
  if (!NetState)
  {
    Log("Please Connect to WI-FI");
    CrabExtern_ReturnNullValue();
    return;
  }    
  
  micoWlanGetIPStatus( &para, Station );
  CrabStringAssignAnsi(Result, para.ip);
}

/*******************************************************************************
* Function    : CrabApiNetGetServerDate
* Caption     : ��ȡ����������
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetServerDate ()
{
  struct tm *      currentTime;
  ntp_timestamp_t  utc_time;
  struct in_addr addr;
  CrabUint  DateOffset;

  CrabString TmpStr;  

  if (CrabExtern_ParamIsString(1))
  {  
    TmpStr = CrabExtern_GetStringParam(1);
  }
  else
  {
    Log("Invaild Param.");
    CrabExtern_ReturnNullValue();
    return;
  }
  
  if (!NetState)
  {
    Log("Please Connect to WI-FI");
    CrabExtern_ReturnNullValue();
    return;
  } 
    
  DateOffset = CrabExtern_GetUintParam(2);
      
  if (GetHostIpByName( TmpStr->Data, &addr ))
  {
    if (sntp_get_time(&addr, &utc_time) == kNoErr)
    {
      currentTime = localtime( (const time_t *)&utc_time);
      CrabExtern_ReturnDateValue(CrabDate_Encode(currentTime->tm_year + 1900, currentTime->tm_mon+1, currentTime->tm_mday + DateOffset));
    }
  }
     
}

/*******************************************************************************
* Function    : CrabApiNetGetServerTime
* Caption     : ��ȡ������ʱ��
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetGetServerTime ()
{
  struct tm *      currentTime;
  ntp_timestamp_t  utc_time;
  struct in_addr addr;
  CrabUint  TimeOffset;

  CrabString TmpStr;  

  if (CrabExtern_ParamIsString(1))
  {  
    TmpStr = CrabExtern_GetStringParam(1);
  }
  else
  {
    Log("Invaild Param.");
    CrabExtern_ReturnNullValue();
    return;
  }
  
  if (!NetState)
  {
    Log("Please Connect to WI-FI");
    CrabExtern_ReturnNullValue();
    return;
  } 
  
  TimeOffset = CrabExtern_GetUintParam(2);
      
  if (GetHostIpByName( TmpStr->Data, &addr ))
  {
    if (sntp_get_time(&addr, &utc_time) == kNoErr)
    {
      currentTime = localtime( (const time_t *)&utc_time);
      CrabExtern_ReturnTimeValue(CrabTime_Encode(currentTime->tm_hour + TimeOffset, currentTime->tm_min,currentTime->tm_sec, 0));
    }
  }
}