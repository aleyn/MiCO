/******************** Copyright wisearm.com *********************************
* File Name         : Gap.cpp
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.1
* Create Date       : 2010-09-16
* Last Update       : 2016-01-12
* Description       : GAP firmware library.
********************************************************************************/
#include "Gap.h"
//#include "SysUtils.h"


/*******************************************************************************
** CRC16��ѯ��                                                                
*******************************************************************************/
#ifdef  __ICCARM__  
      GapWord   //���뵽�ڴ��У�CRC�����һЩ
#else
const GapWord 
#endif  
GAP_CRC_TABLE[16] = {
      0x0000, 0x1021, 0x2042, 0x3063,
      0x4084, 0x50a5, 0x60c6, 0x70e7,
      0x8108, 0x9129, 0xa14a, 0xb16b,
      0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};

/*******************************************************************************
* Function    : GapCommandToRespond
* Caption     : ������תΪ�ظ�
*  @Param     : 1.Cmd - ����
* Return      : GapByte
* Description : .
*******************************************************************************/
GapByte GapCommandToRespond(GapByte Cmd)
{
  GapByte Result = 0;
  
  switch (Cmd)
  {
    case  GAP_CMD_DETECT: { Result = GAP_RPD_DETECT;  break;}
    case  GAP_CMD_SETUP:  { Result = GAP_RPD_SETUP;   break;}
    case  GAP_CMD_READ:   { Result = GAP_RPD_READ;    break;}
    case  GAP_CMD_WRITE:  { Result = GAP_RPD_WRITE;   break;}
    case  GAP_CMD_CONTROL:{ Result = GAP_RPD_CONTROL; break;}
    case  GAP_CMD_ECHO:   { Result = GAP_RPD_ECHO;    break;}
  }
  
  return Result;
}

/*******************************************************************************
* Function    : GapEncodeChar
* Caption     : �Ե�ǰ���ݽ��б���
*  @Param     : 1.Data - Դʼ����
* Return      : GapByte
* Description : ���Դʼ���ݱ�ת�壬�򷵻�ת�������ݣ����򷵻�0
*******************************************************************************/
GapByte GapEncodeChar(GapByte Data)
{
  GapByte Result;

  switch (Data)
  {
    case GAP_PTC_BEGIN: {Result = GAP_ESC_BEGIN; break;}
    case GAP_PTC_END:   {Result = GAP_ESC_END;   break;}
    case GAP_PTC_CRC:   {Result = GAP_ESC_CRC;   break;}
    case GAP_PTC_RS:    {Result = GAP_ESC_RS;    break;}
    case GAP_PTC_ESC:   {Result = GAP_ESC_DOL;   break;}
    default: {Result = 0;}
  }

  return Result;
}

/*******************************************************************************
* Function    : GapDecodeChar
* Caption     : �Ե�ǰ���ݽ��н���
*  @Param     : 1.Data - �ѱ��������
* Return      : GapByte
* Description : ���Դʼ���ݱ�ת�壬�򷵻�ת��ǰ��Դʼ���ݣ����򷵻�0
*******************************************************************************/
GapByte GapDecodeChar(GapByte Data)
{
  GapByte Result;

  switch (Data)
  {
    case GAP_ESC_BEGIN: {Result = GAP_PTC_BEGIN; break;}
    case GAP_ESC_END:   {Result = GAP_PTC_END;   break;}
    case GAP_ESC_CRC:   {Result = GAP_PTC_CRC;   break;}
    case GAP_ESC_RS:    {Result = GAP_PTC_RS;    break;}
    case GAP_ESC_DOL:   {Result = GAP_PTC_ESC;   break;}
    default: {Result = 0;}
  }

  return Result;
}

/*******************************************************************************
* Function    : GapInit
* Caption     : ��ʼ��GAP
*  @Param     : 1.Gap - GAP�ṹָ��
*  @Param     : 2.Buffer - GAP���ݻ�����
*  @Param     : 3.Count - ��������С
* Description : .
*******************************************************************************/
void GapInit(PGap Gap, GapByte *Buffer, GapWord Count)
{
  Gap->SourceBuffer = Buffer;
  Gap->SourceSize = Count;
  GapReset(Gap);
}

/*******************************************************************************
* Function    : GapReset
* Caption     : ��λGAP
*  @Param     : 1.Gap - 
* Description : �����ǰ��״̬���ظ�������״̬
*******************************************************************************/
void GapReset(PGap Gap)
{
  Gap->ResultSize = 0;
  Gap->CRC_In = 0;
  Gap->CRC_Out = 0;
  //Gap->Status = GAP_EncodeStandBy;
}

/*******************************************************************************
* Function    : GapEncodeBuffer
* Caption     : �����û����ݵ�������
*  @Param     : 1.Gap - GAP�ṹ
*  @Param     : 2.GapData - �û�����
*  @Param     : 3.Count - ���ݸ���
* Return      : GapByte ��ǰ�Ѵ���ġ����ͻ�����������
* Description : �Ե�ǰ���ݽ��б��룬���ŵ����ͻ�����
*******************************************************************************/
GapByte GapEncodeBuffer(PGap Gap, PGapData GapData, GapWord Count)
{
  GapByte  *Buffer = (GapByte *)GapData;
  GapWord   BufferSize = Count;
  GapByte   TmpData = 0;
  GapByte  *CurrentBuffer = Gap->SourceBuffer;
  GapWord   CurrentSize = Gap->SourceSize;
  GapByte   Status;

  if ((BufferSize == 0) || (CurrentSize == 0))
  {
    return GAP_Faild;
  }  
  
  Status = GAP_Pressing;

  *CurrentBuffer++ = GAP_PTC_BEGIN;
  CurrentSize--;
  
  while ((CurrentSize > 0 ) && (BufferSize > 0))
  {
    TmpData = GapEncodeChar(*Buffer);

    if (TmpData != 0)
    {
      *CurrentBuffer++ = GAP_PTC_ESC;
      CurrentSize--;

      if (CurrentSize > 0)
      {
        *CurrentBuffer++ = TmpData;
        CurrentSize--;
      }
      else
      {
        Status = GAP_OutBuffer;
        break;
      }
    }
    else
    {
      *CurrentBuffer++ = *Buffer;
      CurrentSize--;
    }
    
    Buffer++;
    BufferSize--;
    
    if (BufferSize == 0)
    {
      if (Status == GAP_InCRC)
      {
        Status = GAP_EndChar;
        break;
      }
      if (Status == GAP_Pressing)
      {
        Status = GAP_InCRC;
        Gap->CRC_Out = GapCalcCrc(GapData, Count);
        Buffer = (GapByte*)&Gap->CRC_Out;
        
        if (CurrentSize > 0)
        {
          *CurrentBuffer++ = GAP_PTC_CRC;
          CurrentSize--;
          BufferSize = 2;
        }
        else
        {
          Status = GAP_OutBuffer;
          break;
        }        
      }
    }
  }
  
  if ((Status == GAP_EndChar) && (BufferSize == 0))
  {
    if (CurrentSize > 0)
    {
      *CurrentBuffer++ = GAP_PTC_END;
      CurrentSize--;
      Gap->ResultSize = Gap->SourceSize - CurrentSize;
      Status = GAP_Success;
    }
    else
    {
      Status = GAP_OutBuffer;
    }   
  }
  else
  {
    Status = GAP_Faild;
  }

  return Status;
}

/*******************************************************************************
* Function    : GapEncodeBuffer
* Caption     : �����û����ݵ�������
*  @Param     : 1.Gap - GAP�ṹ
*  @Param     : 2.GapData - �û�����
*  @Param     : 3.Count - ���ݸ���
* Return      : GapByte ��ǰ�Ѵ���ġ����ͻ�����������
* Description : �Ե�ǰ���ݽ��б��룬���ŵ����ͻ�����
*******************************************************************************/

/*******************************************************************************
* Function    : GapDecodeBuffer
* Caption     : ���뻺�������û�����
*  @Param     : 1.Gap - GAP�ṹ
*  @Param     : 2.GapData - �û�����
*  @Param     : 3.Count - ���ݸ���
* Return      : GapByte
* Description : �Ի��������н��룬���ŵ����û�������
*******************************************************************************/
GapByte GapDecodeBuffer(PGap Gap, PGapData GapData, GapWord Count)
{
  GapByte  *Buffer = (GapByte *)GapData;
  GapWord   BufferSize = Count;
  GapByte   TmpData = 0;
  GapByte  *CurrentBuffer = Gap->SourceBuffer;
  GapWord   CurrentSize = Gap->SourceSize;
  GapByte   Status;

  if ((BufferSize == 0) || (CurrentSize == 0))
  {
    return GAP_Faild;
  }  
  
  Status = GAP_StandBy;
  
  while (CurrentSize > 0)
  {
    TmpData = *CurrentBuffer;
    CurrentBuffer++;
    CurrentSize--;
    
    if (TmpData == GAP_PTC_BEGIN)
    {
      if (Status == GAP_StandBy)
      {
        Status = GAP_Pressing;
      }
      else
      {
        Status = GAP_Faild;
        break;
      }
    }
    else if (TmpData == GAP_PTC_RS)
    {
      //do nothing;
    }
    else if (TmpData == GAP_PTC_END)
    {
      if (Status == GAP_InCRC)
      {
        Status = GAP_EndChar;
      }
      else
      {
        Status = GAP_Faild;
      }
      break;
    }
    else if (TmpData == GAP_PTC_CRC)
    {
      if (Status == GAP_Pressing)
      {
        Status = GAP_InCRC;
        Gap->ResultSize = Count - BufferSize;
        Buffer = (GapByte*)&Gap->CRC_In;
        BufferSize = 2;
      }
      else
      {
        Status = GAP_Faild;
        break;
      }
    }
    else if ((Status == GAP_Pressing) || (Status == GAP_InCRC))
    {
      if (TmpData == GAP_PTC_ESC)
      {
        if (CurrentSize >0)
        {
          TmpData = GapDecodeChar(*CurrentBuffer);
          CurrentBuffer++;
          CurrentSize--;
        }
        else
        {
          Status = GAP_OutBuffer;
          break;
        }
      }

      if (BufferSize > 0)
      {
        *Buffer++ = TmpData;
        BufferSize--;
      }
      else
      {
        Status = GAP_OutBuffer;
        break;
      }
    }
  }

  if (Status == GAP_EndChar)
  {
    Gap->CRC_Out = GapCalcCrc(GapData, Gap->ResultSize);
    if (Gap->CRC_In == Gap->CRC_Out)
    {
      Status = GAP_Success;
    }
  }
  
  return Status;
}

/*******************************************************************************
* Function    : GapCalcCrc
* Caption     : ����CRC����
*  @Param     : 1.GapData - ����ָ��
*  @Param     : 2.Count - ���ݳ���
* Return      : GapWord - CRC 16λ����
* Description : .
*******************************************************************************/
GapWord GapCalcCrc(PGapData GapData, GapWord Count)
{
  GapByte *ptr = (GapByte*) GapData;
  GapWord Crc = 0;
  GapByte da;

  while(Count)
  {
    da = Crc >> 12;
    Crc <<= 4;
    da ^= *ptr >> 4;
    Crc ^= GAP_CRC_TABLE[da];
    
    da = Crc >> 12;
    Crc <<= 4;
    da ^= *ptr & 0x0f;
    Crc ^= GAP_CRC_TABLE[da];
    
    ptr++;
    Count--;
  }
  
  return(Crc);
}

/*******************************************************************************
* Function    : GapContinueCrc
* Caption     : ����CRC����
*  @Param     : 1.Data - ����
*  @Param     : 2.Crc - ԴʼCrc
* Return      : GapWord - CRC 16λ����
* Description : .
*******************************************************************************/
GapWord GapContinueCrc(GapByte Data, GapWord Crc)
{
    GapByte da;

    da = Crc >> 12;
    Crc <<= 4;
    da = da ^ (Data >> 4);
    Crc ^= GAP_CRC_TABLE[da];

    da = Crc >> 12;
    Crc <<= 4;
    da = da ^ (Data & 0x0f);
    Crc ^= GAP_CRC_TABLE[da];

    return Crc;
}


/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
