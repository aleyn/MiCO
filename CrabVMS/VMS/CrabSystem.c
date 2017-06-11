/******************** Copyright wisearm.com *********************************
* File Name         : CrabSystem.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ϵͳӲ��������
********************************************************************************/
#include "CrabVMS.h"
#include "CrabSystem.h"

typedef struct {
  uint8_t NewStatus;
  uint8_t Count;
  uint8_t Tick;
  uint8_t Flash;
  uint8_t Status;
} TSYSLED;

typedef struct{ 
  uint8_t Count;
  uint8_t Down;
} TESCKEY;

typedef struct{
  uint8_t NewStatus;
  uint8_t Flash;
  uint8_t Width;
  uint8_t Count;
  uint8_t Tick;
  uint8_t Status;
} TSYSBEP;

static TSYSLED SysLed;
static TESCKEY EscKey;
static TSYSBEP SysBep;

extern CrabByte CrabAppStatus;

void SYSLED_Process();
void ESCKEY_Process();
void SYSBEP_Process();

/*******************************************************************************
* Function    : CrabSystem_Running
* Caption     : .
* Description : .
*******************************************************************************/
void CrabSystem_Running()
{
  CrabCreateTask(CRAB_TASK_SYSTEM);
  //vTaskStartScheduler();
}

/*******************************************************************************
* Function    : CrabSystemTask
* Caption     : ϵͳ������
* Description : .
*******************************************************************************/
void CrabSystemTask()
{ 
  EscKey.Count = 0;
  SysBep.NewStatus = 0xFF;  
  
  SysLed.NewStatus = CRAB_LED_GREEN_ON;
  SYSLED_Process();
  
  CrabHW_InitExtern();
  
  CrabCreateTask(CRAB_TASK_COMMAND);
  CrabCreateTask(CRAB_TASK_DEBUG);
  CrabCreateTask(CRAB_TASK_EVENT);
  CrabCreateTask(CRAB_TASK_APPLICATION);
  CrabDelay(10);
  
  SysLed.NewStatus = CRAB_LED_RED_ON;

  for(;;)
  {
    SYSLED_Process();
    ESCKEY_Process();
    SYSBEP_Process();
    
    CrabDelay(CRAB_SYSTEM_TICK);
  }    
}

/*******************************************************************************
* Function    : SYSLED_Process
* Caption     : ϵͳLED��ʾ״̬����
* Description : .
*******************************************************************************/
void SYSLED_Process()
{
  if (SysLed.NewStatus != 0xFF)
  {
    switch (SysLed.NewStatus)
    {
      case CRAB_LED_RED_ERROR:
      case CRAB_LED_GREEN_ERROR:
      {
        SysLed.Count = 2;
        SysLed.Flash = 1;
        break;
      }
      case CRAB_LED_GREEN_FLASH:
      case CRAB_LED_RED_FLASH:
      {
        SysLed.Count = 10;
        SysLed.Flash = 1;
        break;
      }
      case CRAB_LED_RED_ON:
      case CRAB_LED_GREEN_ON:
      {
        SysLed.Count = 0;
        SysLed.Flash = 0;
        break;
      }
      default:
      {
        SysLed.Count = 0;
        SysLed.Flash = 0;
      }
    }
    
    switch (SysLed.NewStatus)
    {
      case CRAB_LED_RED_ERROR:
      case CRAB_LED_RED_FLASH:
      case CRAB_LED_RED_ON:
      {
        SysLed.Status = 1;
        break;
      }
      case CRAB_LED_GREEN_FLASH:
      case CRAB_LED_GREEN_ERROR:
      case CRAB_LED_GREEN_ON:
      {
        SysLed.Status = 2;
        break;
      }
      default:
      {
        SysLed.Status = 0;
      }
    }
    
    SysLed.Tick = 1;
    SysLed.NewStatus = 0xFF;
  }
  
  if (SysLed.Status)
  {
    if (SysLed.Count)
    {
      if (SysLed.Tick > 1)
      {
        SysLed.Tick--;
      }
      else
      {
        if (SysLed.Flash)
        {          
          if (SysLed.Status == 1)
          {
            CrabHW_LED_ChangeSys(CRAB_LED_RED_ON);
          }
          else
          {
            CrabHW_LED_ChangeSys(CRAB_LED_GREEN_ON);
          }
        }
        else
        {
          CrabHW_LED_ChangeSys(CRAB_LED_OFF);
        }
        
        SysLed.Flash = 1 - SysLed.Flash;
        SysLed.Tick = SysLed.Count;
      }
    }
    else
    {
      if (SysLed.Tick)
      {
        if (SysLed.Status == 1)
        {
          CrabHW_LED_ChangeSys(CRAB_LED_RED_ON);
        }
        else
        {
          CrabHW_LED_ChangeSys(CRAB_LED_GREEN_ON);
        }
        
        SysLed.Tick = 0;
      }
    }
  }
  else
  {
    if (SysLed.Tick)
    {
      CrabHW_LED_ChangeSys(CRAB_LED_OFF);
      SysLed.Tick = 0;
    }
  }
}

/*******************************************************************************
* Function    : ESCKEY_Process
* Caption     : ϵͳESC��������
* Description : .
*******************************************************************************/
void ESCKEY_Process()
{
  if (GPIO_GetInputBit(SYS_ESC) == 0)
  {
    if (EscKey.Count < 200) EscKey.Count++;
    if (EscKey.Count > 20)
    {
      if (EscKey.Down !=1)
      {
        EscKey.Down = 1;
        
        if (CrabAppStatus == CRAB_APP_RUNNING)
        {
          CrabChangeAppState(CRAB_APP_STOPPING);          
          //CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_PAUSE)
        {
          CrabChangeAppState(CRAB_APP_STOPPING);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus != CRAB_APP_OFF)
        {
          CrabChangeAppState(CRAB_APP_OFF); 
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
      }
    }
  }
  else
  {
    if (EscKey.Count > 1)
    {
      if (EscKey.Count < 20)
      {
        if (CrabAppStatus == CRAB_APP_RUNNING)
        {
          CrabChangeAppState(CRAB_APP_PAUSE);
          //CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_PAUSE)
        {
          CrabChangeAppState(CRAB_APP_CONTINUE);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
        else if (CrabAppStatus == CRAB_APP_OFF)
        {
          CrabChangeAppState(CRAB_APP_LOADROM);
          CrabTaskResume(CRAB_TASK_APPLICATION);
        }
          
      }
    }
    
    EscKey.Count = 0;
    EscKey.Down = 0;
  }
}

/*******************************************************************************
* Function    : SYSBEP_Process
* Caption     : ϵͳ����������
* Description : .
*******************************************************************************/
void SYSBEP_Process()
{
  if (SysBep.NewStatus != 0xFF)
  {
    if (SysBep.NewStatus)
    {
      CrabHW_BEEP_Enable();
      SysBep.Flash = 0;
    }
    else
    {
      CrabHW_BEEP_Disable();
    }
    
    SysBep.Tick = 1;
    SysBep.Status = SysBep.NewStatus;
    SysBep.NewStatus = 0xFF;
  }
  
  if (SysBep.Status)
  {
    if (SysBep.Width)
    {
      if (SysBep.Tick > 1)
      {
        SysBep.Tick--;
      }
      else if (SysBep.Count)
      {
        SysBep.Tick = SysBep.Width;
        SysBep.Flash = 1 - SysBep.Flash;
        
        if (SysBep.Flash)
        {
          CrabHW_BEEP_Start();
        }
        else
        {
          CrabHW_BEEP_Stop();          
          SysBep.Count --;
        }
      }
      else
      {
        CrabHW_BEEP_Stop();        
        SysBep.Status = CRAB_BEEP_STOP;
        SysBep.Tick = 0;
      }
    }
    else
    {
      if (SysBep.Count)
      {
        if (SysBep.Flash == 0)
        {
          SysBep.Tick = SysBep.Count;
          SysBep.Flash = 1;
          CrabHW_BEEP_Start();
        }
        else if (SysBep.Tick > 1)
        {
          SysBep.Tick --;
        }
        else
        {
          CrabHW_BEEP_Stop(); 
          
          SysBep.Status = CRAB_BEEP_STOP;
          SysBep.Tick = 0;
        }
      }
      else
      {
        if (SysBep.Flash == 0)
        {
          SysBep.Flash = 1;
          CrabHW_BEEP_Start();
        }
      }
    }
  }
  else
  {
    if (SysBep.Tick)
    {
      CrabHW_BEEP_Stop(); 
      SysBep.Tick = 0;
    }
  }
}

/*******************************************************************************
* Function    : CrabChangeLEDStatus
* Caption     : ����ϵͳLED��ʾ״̬
*  @Param     : 1.Status - �µ�״̬
* Description : .
*******************************************************************************/
void CrabChangeLEDStatus(CrabByte Status)
{
  SysLed.NewStatus = Status; 
  CrabTaskResume(CRAB_TASK_SYSTEM);
}

/*******************************************************************************
* Function    : CrabChangeBeep
* Caption     : ����ϵͳ��������������
*  @Param     : 1.Width - Ƶ�ʿ��
*  @Param     : 2.Count - ��������
* Description : .
*******************************************************************************/
void CrabChangeBeep(CrabByte Width, CrabByte Count)
{
  if ((Width == 0) || (Count ==0))
  {
    SysBep.Count = 0;
    SysBep.Width = 0;
    SysBep.NewStatus = CRAB_BEEP_STOP;
  }
  else
  {
    SysBep.Count = Count;
    SysBep.Width = Width * 2;
    SysBep.NewStatus = CRAB_BEEP_START;
  } 
  CrabTaskResume(CRAB_TASK_SYSTEM);
}

// END OF FILE