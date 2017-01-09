/********************************************************************************
* File Name   : CrabStoreStream.c
* Author      : �ⴴ��(aleyn.wu)
* Version     : V1.0.0
* Create Date : 2015-10-12
* Last Update : 2016-12-07
* Description : StoreStream for MiCO
********************************************************************************/
#include "CrabVMS.h"
#include "common.h"
#include "platform_peripheral.h"
#include "mico_platform.h"

#define FlashProtectMask     0x1C
#define FlashProtectEnable   0x1C
#define FlashProtectDisable  0x00

CrabUint CrabStoreStream_GetSize(TCrabStreamDevice Device);
CrabUint CrabStoreStream_SetSize(TCrabStreamDevice Device, CrabUint Size);
CrabUint CrabStoreStream_Position(TCrabStreamDevice Device);
CrabUint CrabStoreStream_Seek(TCrabStreamDevice Device, CrabUint Offset, CrabInt Origin);
CrabBool CrabStoreStream_Eof(TCrabStreamDevice Device);
CrabUint CrabStoreStream_Free(TCrabStreamDevice Device);

CrabUint CrabStoreStream_ReadFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
CrabUint CrabStoreStream_WriteFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);

CrabUint CrabStoreStream_ReadEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
CrabUint CrabStoreStream_WriteEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);

/********************************************************************************
* Function    : CrabStoreStream_Create()
* Caption     : �����ļ���
*  @Param     : Stream - ���ṹ
*  @Param     : StoreInfo - �洢��Ϣ�ṹ
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Create(PCrabStream Stream, CrabStoreInfo StoreInfo)
{  
  if (StoreInfo != null)
  {
    Stream->Device = (TCrabStreamDevice)StoreInfo;
    Stream->GetSize = CrabStoreStream_GetSize;
    Stream->SetSize = CrabStoreStream_SetSize;
    Stream->Position = CrabStoreStream_Position;
    Stream->Seek = CrabStoreStream_Seek;
    Stream->Eof = CrabStoreStream_Eof;
    Stream->Free = CrabStoreStream_Free;

    switch (StoreInfo->Type)
    {
      case CRAB_STORE_TYPE_FLASH:
      {
        Stream->Read = CrabStoreStream_ReadFlash;
        Stream->Write = CrabStoreStream_WriteFlash;
        break;
      }
      case CRAB_STORE_TYPE_EEPROM:
      {
        Stream->Read = CrabStoreStream_ReadEEprom;
        Stream->Write = CrabStoreStream_WriteEEprom;
        break;
      }
    }   

   StoreInfo->Addr = 0;
   return Stream->Device;
  }
  else
  {
    CrabStream_Init(Stream);
    return CrabStream_Error;
  }

}

/********************************************************************************
* Function    : CrabStoreStream_Free()
* Caption     : �ͷ��ļ���
*  @Param     : Stream - ���ṹ
* Return      : CrabUint
* Description : �ļ������ӦStream.Device
********************************************************************************/
CrabUint CrabStoreStream_Free(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Create()
* Caption     : ��������Ϣ
*  @Param     : Stream - ���ṹ
*  @Param     : Offset - ����ƫ��λ��
*  @Param     : Size - ����С
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Update(PCrabStream Stream, CrabUint Offset, CrabUint Size)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;

  if (StoreInfo != null)
  {
    StoreInfo->Offset = Offset;
    StoreInfo->Size = Size;
    StoreInfo->Addr = 0;
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteProtect()
* Caption     : �򿪻����洢����д����
*  @Param     : Stream - ���ṹ
*  @Param     : State - д����״̬
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_WriteProtect(PCrabStream Stream, CrabBool State)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;
  //CrabByte Tmp;

  if (StoreInfo != null)
  {
    if (StoreInfo->Type == CRAB_STORE_TYPE_FLASH)
    {

      if (State)
      {
        State = FlashProtectEnable;
      }
      else
      {
        State = FlashProtectDisable;
      }

      /*
      // MiCO��֧��
      sFLASH_WriteStatus(State);
      Tmp = sFLASH_ReadStatus();
      
      if ((Tmp & FlashProtectMask) == State)
      {
        return CrabTrue;
      }
      else
      {
        return CrabFalse;
      }
      */
    }
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_EarseAll()
* Caption     : ɾ�����е�����
*  @Param     : Stream - ���ṹ
*  @Param     : State - д����״̬
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_EarseAll(PCrabStream Stream)
{
  CrabUint I;
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;

  if (StoreInfo != null)
  {
    if (StoreInfo->Type == CRAB_STORE_TYPE_FLASH)
    {  
      // MiCO��֧��ȫ�����
      /*
      sFLASH_EraseBulk();
      sFLASH_WaitForWriteEnd();
      */
      
      for (I=0; I<CRAB_FLASH_SECTION_COUNT; I++)
      {
        //Log("Erase Flash (%d)K...", I * 64);
        MicoFlashErase((mico_partition_t)MICO_PARTITION_FILESYS, I * CRAB_FLASH_SECTION_SIZE, CRAB_FLASH_SECTION_SIZE);
        //CrabDelay(10);
      }
    }
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteProtect()
* Caption     : ɾ����������
*  @Param     : Stream - ���ṹ
*  @Param     : SecAddr - ������ַ
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_EarseSector(PCrabStream Stream, CrabUint SecAddr, CrabUint Count)
{
  CrabStoreInfo StoreInfo = (CrabStoreInfo)Stream->Device;
  CrabUint I;

  if (StoreInfo != null)
  {
    if (StoreInfo->Type == CRAB_STORE_TYPE_FLASH)
    {
      //MicoFlashErase((mico_partition_t)MICO_PARTITION_FILESYS, SecAddr, FlashSectionMax);
      
      if (Count > CRAB_FLASH_SECTION_COUNT)
      {
        Count = CRAB_FLASH_SECTION_COUNT;
      }

      for (I=0; I<Count; I++)
      {
        MicoFlashErase((mico_partition_t)MICO_PARTITION_FILESYS, SecAddr, CRAB_FLASH_SECTION_SIZE);
        SecAddr += CRAB_FLASH_SECTION_SIZE;
      }      
    }
    
    return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_GetSize()
* Caption     : ȡ���ļ�����С
*  @Param     : Device - �ļ����
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_GetSize(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    return ((CrabStoreInfo)Device)->Size;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_SetSize()
* Caption     : �����ļ�����С
*  @Param     : Device - �ļ����
*  @Param     : Size - ��С
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_SetSize(TCrabStreamDevice Device, CrabUint Size)
{
  if (Device != CrabStream_InvaildDevice)
  {
		//δʵ��
		return 0;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Position()
* Caption     : ȡ���ļ�����ǰλ��
*  @Param     : Device - �ļ����
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Position(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    return ((CrabStoreInfo)Device)->Addr;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Seek()
* Caption     : ��λ�ļ���λ��
*  @Param     : Device - �ļ����
*  @Param     : Offset - ƫ��ֵ
*  @Param     : Origin - ƫ��ģʽ
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_Seek(TCrabStreamDevice Device, CrabUint Offset, CrabInt Origin)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;

    switch (Origin)
    {
      case csoBeginning:
      {
        StoreInfo->Addr = Offset;
        break;
      }
      case csoCurrent:
      {
        StoreInfo->Addr += Offset;
        break;
      }
      case csoEnd:
      {
        StoreInfo->Addr = StoreInfo->Size - Offset;
        break;
      }
    }
    
    return StoreInfo->Addr;
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_ReadFlash()
* Caption     : ��ȡ�ļ�������
*  @Param     : Device - �ļ����
*  @Param     : Buffer - ������
*  @Param     : Count - ����
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_ReadFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr;      
      MicoFlashRead((mico_partition_t)MICO_PARTITION_FILESYS, &Addr, Buffer, Count);
      StoreInfo->Addr += Count;

      return Count;
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteFlash()
* Caption     : д���ļ�������
*  @Param     : Device - �ļ����
*  @Param     : Buffer - ������
*  @Param     : Count - ����
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_WriteFlash(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr; 
      MicoFlashWrite((mico_partition_t)MICO_PARTITION_FILESYS, &Addr, Buffer, Count);
      StoreInfo->Addr += Count;
      
      return Count;
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_ReadEEprom()
* Caption     : ��ȡ�ļ�������
*  @Param     : Device - �ļ����
*  @Param     : Buffer - ������
*  @Param     : Count - ����
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_ReadEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr;      
      if (EEPROM_BufferRead(Buffer, Addr, Count) == EEPROM_Success)
      {
        StoreInfo->Addr += Count;

        return Count;
      }
      else
      {
        return CrabStream_Error;
      }
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_WriteEEprom()
* Caption     : д���ļ�������
*  @Param     : Device - �ļ����
*  @Param     : Buffer - ������
*  @Param     : Count - ����
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabUint CrabStoreStream_WriteEEprom(TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    CrabUint  Addr;

    if ((StoreInfo->Addr + Count) <= StoreInfo->Size)
    {
      Addr = StoreInfo->Offset + StoreInfo->Addr; 
      if (EEPROM_BufferWrite(Buffer, Addr, Count) == EEPROM_Success)
      {
        StoreInfo->Addr += Count;
        return Count;
      }
      else
      {
        return CrabStream_Error;
      }      
    }
    else
    {
      return CrabStream_Error;
    }
  }
  else
  {
    return CrabStream_Error;
  }
}

/********************************************************************************
* Function    : CrabStoreStream_Eof()
* Caption     : �ж��ļ����Ƿ��Ѿ�����
*  @Param     : Device - 
* Return      : CrabUint
* Description : .
********************************************************************************/
CrabBool CrabStoreStream_Eof(TCrabStreamDevice Device)
{
  if (Device != CrabStream_InvaildDevice)
  {
    CrabStoreInfo StoreInfo = (CrabStoreInfo)Device;
    
    if (StoreInfo->Addr >= StoreInfo->Size)
    {
      return CrabTrue;
    }
    else
    {
      return CrabFalse;
    }
  }
  else
  {
    return CrabTrue;
  }
}

