/******************** Copyright wisearm.com *********************************
* File Name         : CrabCommand.c
* Author            : �ⴴ��(aleyn.wu) 
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ͨѶ���������
********************************************************************************/
#include "CrabVMS.h"
#include "CrabCommand.h"
#include "CrabStoreStream.h"
#include "CrabVersionFW.h"
#include "CrabHardware.h"
#include "Gap.h"

extern GapByte GapBuffer[GAP_ENCODE_SIZE];
__cache TGapData GapTx;
__cache TGapData GapRx1;
__cache TGapData GapRx2;

CrabBool Cmd_DeviceDetect(PGapData GapCmd);
CrabBool Cmd_Setup(PGapData GapCmd);
CrabBool Cmd_Read(PGapData GapCmd);
CrabBool Cmd_Write(PGapData GapCmd);
CrabBool Cmd_Control(PGapData GapCmd);
CrabBool Cmd_Echo(PGapData GapCmd);

/*******************************************************************************
* Function    : USB_OnDecodeGap
* Caption     : .
* Description : .
*******************************************************************************/
void USB_OnDecodeGap()
{
  CrabTaskResumeFromISR(CRAB_TASK_COMMAND);
}

/*******************************************************************************
* Function    : USB_OnRunScript
* Caption     : .
*  @Param     : 1.State - 
* Description : .
*******************************************************************************/
void USB_OnRunScript(uint8_t State)
{
  CrabChangeAppState(State);  
  CrabTaskResumeFromISR(CRAB_TASK_APPLICATION);
}

/*******************************************************************************
* Function    : CrabCommandTask
* Caption     : ͨѶ��������
* Description : .
*******************************************************************************/
void CrabCommandTask()
{
  TGap        Gap;
  PGapData    GapCmd = &GapRx1;
  PGapData    GapRx = &GapRx1;
  CrabUint    Status = CrabFalse;
  CrabByte    GapIndex = 1;
  
  GapInit(&Gap, GapBuffer, GAP_ENCODE_SIZE);
  CrabCreateStoreStream();  
  USB_Enable();
  CrabTaskSuspend(CRAB_TASK_COMMAND);
  
  while (1)
  {
    if (USB_ReceiveSuccess()) //�����λ��������
    {
      CrabChangeLEDStatus(CRAB_LED_RED_FLASH);
      
      if (GapDecodeBuffer(&Gap, GapRx, sizeof(TGapData)) == GAP_Success)
      {
        GapCmd = GapRx;
  
        if (GapIndex == 1)
        {
          GapIndex = 2;
          GapRx = &GapRx2;
        }
        else
        {
          GapIndex = 1;
          GapRx = &GapRx1;
        }

        USB_ReceiveComplete(USBGAP_SUCCESS);
      }
      else
      {
        USB_ReceiveComplete(USBGAP_FAILD);
        continue;
      }
    }
    else
    {
      CrabChangeLEDStatus(CRAB_LED_RED_ON);
      CrabTaskSuspend(CRAB_TASK_COMMAND);
      continue;
    }
    
    switch (GapCmd->Command)
    {
      case GAP_CMD_DETECT:
      {
        Status = Cmd_DeviceDetect(GapCmd); 
        break;
      }
      case GAP_CMD_SETUP:
      {       
        Status = Cmd_Setup(GapCmd);
        break;
      }
      case GAP_CMD_READ:
      {
        Status = Cmd_Read(GapCmd);     
        break;
      }
      case GAP_CMD_WRITE:
      {
        Status = Cmd_Write(GapCmd);
        break;
      }
      case GAP_CMD_CONTROL:
      {
        Status = Cmd_Control(GapCmd);        
        break;
      }
      case GAP_CMD_ECHO:
      {
        Status = Cmd_Echo(GapCmd); 
        break;
      }
    }
    
    GapTx.Respond = GapCommandToRespond(GapCmd->Command);

    if (Status)
    {
      GapTx.Status = GAP_STS_SUCCESS;
    }
    else
    {
      GapTx.Status = GAP_STS_FAILED;
      GapTx.Size = 0;
    }
    
    //�ظ�����λ��
    if (GapEncodeBuffer(&Gap, &GapTx, GapGetSize(GapTx)) == GAP_Success)
    {
      //cmd_log("Command = %2.2x, Respond = %2.2x;", GapCmd->Command, GapTx.Respond);
      USB_TransmitComplete(USBGAP_SUCCESS, Gap.ResultSize);
    }
    else
    {
      USB_TransmitComplete(USBGAP_FAILD, 0);
    }
  }
}

/*******************************************************************************
* Function    : Cmd_DeviceDetect
* Caption     : .
*  @Param     : 1.GapCmd - 
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool Cmd_DeviceDetect(PGapData GapCmd)
{
  GapTx.Detect.DeviceID = CRAB_DEVICE_ID;
  GapTx.Detect.VenderID = CRAB_VENDER_ID;
  GapTx.Detect.Hardware.uVerInfo = CRAB_HW_VER;
  GapTx.Detect.Firmware.Major = CRAB_FW_VERSION_MAJOR;     //���汾
  GapTx.Detect.Firmware.Minor = CRAB_FW_VERSION_MINOR;     //���汾
  GapTx.Detect.Firmware.Build = CRAB_FW_VERSION_BUILD;     //�����
  GapTx.Size = sizeof(TGapDetect);
  return CrabTrue;
}

/*******************************************************************************
* Function    : Cmd_Setup
* Caption     : .
*  @Param     : 1.GapCmd - 
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool Cmd_Setup(PGapData GapCmd)
{
  CrabBool Status = CrabFalse;

  switch (GapCmd->Detail)
  {
    case 0: //Ӳ������
    {
      Status = CrabTrue;
      GapTx.Size = 0;
      CrabTaskResume(CRAB_TASK_DEBUG);
      break;
    }
    
    case 1: //�洢��д��������
    {
      CrabStoreStream_WriteProtect(&FlashStream, GapCmd->Setup.bParam[0]);
      Status = CrabTrue;
      GapTx.Size = 0;
      break;
    }
    case 2: //����APP����״̬
    {
      CrabChangeAppState(GapCmd->Setup.bParam[0]);
      CrabTaskResume(CRAB_TASK_APPLICATION);
      GapTx.Size = 0;
      Status = CrabTrue;
      break;
    }
    case 8: //�洢��ȫ�̲���
    {
      CrabStoreStream_EarseAll(&FlashStream);
      Status = CrabTrue;
      GapTx.Size = 0;
      break;
    }
  }

  return Status;
}

/*******************************************************************************
* Function    : Cmd_Read
* Caption     : .
*  @Param     : 1.GapCmd - 
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool Cmd_Read(PGapData GapCmd)
{
  CrabBool Status = CrabFalse;
  CrabUint Count;
  CrabUint Tmp;

  switch (GapCmd->Detail)
  {
    case 1: //�洢�����ݶ�
    {
      Count = GapCmd->ReadWrite.Count;
            
      if (Count > GAP_DATA_SIZE)
      {
        Count = GAP_DATA_SIZE;
      }
            
      if (Count)
      {                    
        GapTx.ReadWrite.Address = GapCmd->ReadWrite.Address;
        GapTx.ReadWrite.Count = Count;
        CrabStream_SeekAddr(&FlashStream, GapTx.ReadWrite.Address);
        Status = CrabStream_Read(&FlashStream, GapTx.ReadWrite.bData, Count);
        
        if (Status)
        {
          GapTx.Size = Count + 8;
        }
      }
      break;
    }
    case 2: //�洢�����������ҿհ�����
    {
      TCrabFileTable FileTable;
            
      Count = GapCmd->ReadWrite.Count;
      
      Tmp = CrabScanFileTable(CRAB_SCAN_LAST_SPACE, &FileTable, Count);
      GapTx.ReadWrite.Address = FileTable.FileAddr;
      GapTx.ReadWrite.Count = FileTable.FileSize;
      GapTx.ReadWrite.uData[0] = Tmp;
      GapTx.Size = 12;
      Status = CrabTrue;

      break;
    }
    case 3: //�洢����������������ļ���
    {
      TCrabFileTable FileTable;
            
      Count = GapCmd->ReadWrite.Count;
      
      Tmp = CrabScanFileTable(CRAB_SCAN_LAST_FILE, &FileTable, Count);
      GapTx.ReadWrite.Address = FileTable.FileAddr;
      GapTx.ReadWrite.Count = FileTable.FileSize;
      GapTx.ReadWrite.uData[0] = Tmp;
      GapTx.Size = 12;
      Status = CrabTrue;

      break;
    }
    case 4: //��ȡ������С�͸���
    {      
      GapTx.ReadWrite.Address = 0;
      GapTx.ReadWrite.Count = CRAB_FLASH_SECTION_COUNT;
      GapTx.ReadWrite.uData[0] = CRAB_FLASH_SECTION_SIZE;
      GapTx.Size = 12;
      Status = CrabTrue;

      break;
    }    
    case 9: //EEPROM ���ݶ�
    {
      Count = GapCmd->ReadWrite.Count;
            
      if (Count > GAP_DATA_SIZE)
      {
        Count = GAP_DATA_SIZE;
      }
            
      if (Count)
      {                    
        GapTx.ReadWrite.Address = GapCmd->ReadWrite.Address;
        GapTx.ReadWrite.Count = Count;
        CrabStream_SeekAddr(&EEpromStream, GapTx.ReadWrite.Address);
        Status = CrabStream_Read(&EEpromStream, GapTx.ReadWrite.bData, Count);

        if (Status)
        {
          GapTx.Size = Count + 8;
        }
      }
      break;
    }
  }

  return Status;
}

/*******************************************************************************
* Function    : Cmd_Write
* Caption     : .
*  @Param     : 1.GapCmd - 
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool Cmd_Write(PGapData GapCmd)
{
  CrabBool Status = CrabFalse;
  CrabUint Count;
  CrabUint Tmp;
  
  switch (GapCmd->Detail)
  {
    case 1: //Flash����д
    {
      Count = GapCmd->ReadWrite.Count;
      if (Count > GAP_DATA_SIZE)
      {
        Count = GAP_DATA_SIZE;
      }
            
      if (Count)
      {         
        GapTx.ReadWrite.Address = GapCmd->ReadWrite.Address;
        GapTx.ReadWrite.Count = Count;
        GapTx.Size = 8;
        
        CrabStream_SeekAddr(&FlashStream, GapCmd->ReadWrite.Address);
        Status = CrabStream_Write(&FlashStream, GapCmd->ReadWrite.bData, Count);        
      }
      break;
    }
    case 2: //Flash����������������
    {
      TCrabFileTable FileTable;
            
      FileTable.FileAddr = GapCmd->ReadWrite.Address;
      FileTable.FileSize = GapCmd->ReadWrite.Count;
      Tmp = CrabUpdateFileTable(GapCmd->ReadWrite.uData[0], &FileTable);
      GapTx.ReadWrite.Address = Tmp;
      GapTx.ReadWrite.Count = sizeof(TCrabFileTable);
      GapTx.Size = 8;
      Status = CrabTrue;

      break;
    }
    case 4: //Flash��������
    {
      Count = GapCmd->ReadWrite.Count;
            
      if (Count)
      {         
        GapTx.ReadWrite.Address = GapCmd->ReadWrite.Address;
        GapTx.ReadWrite.Count = Count;
        GapTx.Size = 8;
        CrabStoreStream_EarseSector(&FlashStream, GapCmd->ReadWrite.Address, Count);
        Status = CrabTrue;
      }
      break;
    }
    case 9: //EEPROM����д
    {
      Count = GapCmd->ReadWrite.Count;
      if (Count > GAP_DATA_SIZE)
      {
        Count = GAP_DATA_SIZE;
      }
            
      if (Count)
      {         
        GapTx.ReadWrite.Address = GapCmd->ReadWrite.Address;
        GapTx.ReadWrite.Count = Count;
        GapTx.Size = 8;
        
        CrabStream_SeekAddr(&EEpromStream, GapCmd->ReadWrite.Address);
        Status = CrabStream_Write(&EEpromStream, GapCmd->ReadWrite.bData, Count);                
      }
      break;
    }
  }

  return Status;
}

/*******************************************************************************
* Function    : Cmd_Control
* Caption     : .
*  @Param     : 1.GapCmd - 
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool Cmd_Control(PGapData GapCmd)
{
  CrabBool Status = CrabTrue;
  
  GapTx.Size = 0;
  //CrabTaskResume(CRAB_TASK_EVENT);
  
  return Status;
}

/*******************************************************************************
* Function    : Cmd_Echo
* Caption     : .
*  @Param     : 1.GapCmd - 
* Return      : CrabBool
* Description : .
*******************************************************************************/
CrabBool Cmd_Echo(PGapData GapCmd)
{
  CrabUint Count = GapCmd->Size;
  memcpy(GapTx.Echo.bReply, GapCmd->Echo.bReply, Count);
  GapTx.Size = Count;
  
  return CrabTrue;
}

// END OF FILE