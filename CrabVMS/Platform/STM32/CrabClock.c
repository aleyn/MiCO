/******************** Copyright wisearm.com *********************************
* File Name         : CrabClock.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : Ӧ��
********************************************************************************/
#include "CrabVMS.h"

RTC_TimeTypeDef RTC_TimeStructure;
RTC_DateTypeDef RTC_DateStructure;

crabapi CrabGetClock();
crabapi CrabSetClock();

/*******************************************************************************
* Function    : CrabRegisterClockApi
* Caption     : ע��ʱ��API���� 
* Description : .
*******************************************************************************/
void CrabRegisterClockApi()
{
  CrabStaticPort.getClock = CrabGetClock;
  CrabStaticPort.setClock = CrabSetClock;
}

/*******************************************************************************
* Function    : CrabGetClock
* Caption     : ��ʱ�Ӷ˿ڶ������ݵ��Ĵ�����
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetClock()
{  
  CrabUint Port = CrabExtern_GetPortAddr();
  
  if (Port != 2)  //����ʱ���ͣ�������������
  {
    /* Get the current Date */
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
    //       RTC_DateStructure.RTC_Year, 
    //       RTC_DateStructure.RTC_Month, 
    //       RTC_DateStructure.RTC_Date, 
    //       RTC_DateStructure.RTC_WeekDay);   
  }
  
  if (Port != 1) //���������ͣ���������ʱ��
  {
    /* Get the current Time and Date */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
    //       RTC_TimeStructure.RTC_Hours,
    //       RTC_TimeStructure.RTC_Minutes, 
    //       RTC_TimeStructure.RTC_Seconds);
    
    /* Unfreeze the RTC DR Register */
    (void)RTC->DR;
  }
  
  //RTC_GetSubSecond()  ����Ǻ���
  
  switch (Port)
  {
    case 1:
    {
      CrabDate Date;
      Date = CrabDate_Encode(RTC_DateStructure.RTC_Year + 2000, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);

      CrabExtern_WriteToPortAsDate(Date);
      break;
    }
    case 2:
    {
      CrabTime Time;
      Time = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds, 0);

      CrabExtern_WriteToPortAsTime(Time);
      break;
    }
    default:
    {
      CrabDatetime Value;
      Value.Date = CrabDate_Encode(RTC_DateStructure.RTC_Year + 2000, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date);
      Value.Time = CrabTime_Encode(RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds, 0);

      CrabExtern_WriteToPortAsDatetime(Value);
    }
  }  
}

/*******************************************************************************
* Function    : CrabSetClock
* Caption     : ���Ĵ���������д�뵽ʱ�Ӷ˿�
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetClock()
{
  CrabUint      Port = CrabExtern_GetPortAddr();
  CrabUShort    Year;
  CrabByte      Month, Day;
  CrabByte      Hour, Min, Sec;
  CrabUShort    MSec;  
  
  if (Port != 2)  //����ʱ���ͣ�������������
  {
    /* Get the current Date */
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    //printf("The current date (yyyy-mm-dd/ww) is :  %0.4d-%0.2d-%0.2d / %0.2d \n", 
    //       RTC_DateStructure.RTC_Year, 
    //       RTC_DateStructure.RTC_Month, 
    //       RTC_DateStructure.RTC_Date, 
    //       RTC_DateStructure.RTC_WeekDay);   
  }
  
  if (Port != 1) //���������ͣ���������ʱ��
  {
    /* Get the current Time and Date */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    //printf("The current time (hh:nn:ss) is :  %0.2d:%0.2d:%0.2d \n", 
    //       RTC_TimeStructure.RTC_Hours,
    //       RTC_TimeStructure.RTC_Minutes, 
    //       RTC_TimeStructure.RTC_Seconds);
    
    /* Unfreeze the RTC DR Register */
    (void)RTC->DR;
  }  
  
  switch (Port)
  {
    case 1:
    {
      CrabDate Date;
      if (!CrabExtern_ReadFromPortAsDate(Date)) return;

      CrabDate_Decode(Date, __ref Year, __ref Month, __ref Day);

      RTC_DateStructure.RTC_Year = Year % 100;
      RTC_DateStructure.RTC_Month = Month;
      RTC_DateStructure.RTC_Date = Day;

      break;
    }
    case 2:
    {
      CrabTime Time;
      if (!CrabExtern_ReadFromPortAsTime(Time)) return;

      CrabTime_Decode(Time, __ref Hour, __ref Min, __ref Sec, __ref MSec);

      RTC_TimeStructure.RTC_Hours = Hour;
      RTC_TimeStructure.RTC_Minutes = Min;
      RTC_TimeStructure.RTC_Seconds = Sec;

      break;
    }
    default:
    {
      CrabDatetime Value;
      if (!CrabExtern_ReadFromPortAsDatetime(Value)) return;

      CrabDate_Decode(Value.Date, __ref Year, __ref Month, __ref Day);

      RTC_DateStructure.RTC_Year = Year % 100;
      RTC_DateStructure.RTC_Month = Month;
      RTC_DateStructure.RTC_Date = Day;
      CrabTime_Decode(Value.Time, __ref Hour, __ref Min, __ref Sec, __ref MSec);

      RTC_TimeStructure.RTC_Hours = Hour;
      RTC_TimeStructure.RTC_Minutes = Min;
      RTC_TimeStructure.RTC_Seconds = Sec;
    }
  }  
  
  if (Port !=2 ) 
  {
    /* Configure the RTC date register */
    if(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure) == ERROR)
    {
      printf("RTC Set Date failed. !!\n");
    } 
    else
    {
      RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    }
  }

  if (Port != 1)
  {
    /* Configure the RTC time register */
    if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) == ERROR)
    {
      printf("RTC Set Time failed. !!\n");
    } 
    else
    {
      RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    }
  }
}
