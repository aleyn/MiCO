/******************** Copyright wisearm.com ************************************
* File Name         : CrabStream.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �ڴ����Ž���
********************************************************************************/

#ifndef __CRAB_STREAM__
#define __CRAB_STREAM__

#include <stdio.h>
#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CrabStream_Error                0xFFFFFFFF
#define CrabStream_InvaildDevice        0

typedef enum
{
	csoBeginning = SEEK_SET,          //����ʼλ�� (SEEK_SET)
	csoCurrent   = SEEK_CUR,          //�ӵ�ǰλ�� (SEEK_CUR)
  csoEnd       = SEEK_END           //�ӽ���λ�� (SEEK_END)
} TCrabStreamOrigin;               //��λģʽ

typedef enum
{
	csmOpenRead = 0,           //ֻ��
	csmOpenWrite = 1,          //ֻд
	csmOpenReadWrite = 2,      //��д
  csmCreate = 3              //����һ�����Զ�д�� 
} TCrabStreamMode;

typedef CrabUint TCrabStreamDevice;

typedef CrabUint(*TCrabStream_GetSize)  (TCrabStreamDevice Device);
typedef CrabUint(*TCrabStream_SetSize)  (TCrabStreamDevice Device, CrabUint Size);
typedef CrabUint(*TCrabStream_Position) (TCrabStreamDevice Device);
typedef CrabUint(*TCrabStream_Seek)     (TCrabStreamDevice Device, CrabUint Offset, CrabInt Origin);
typedef CrabUint(*TCrabStream_Read)     (TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
typedef CrabUint(*TCrabStream_Write)    (TCrabStreamDevice Device, CrabPoint Buffer, CrabUint Count);
typedef CrabBool(*TCrabStream_Eof)      (TCrabStreamDevice Device);
typedef CrabUint(*TCrabStream_Free)     (TCrabStreamDevice Device);

//�ڴ����ṹ����
typedef struct
{
  TCrabStreamDevice    Device;        //�豸��Ϣ

  TCrabStream_GetSize  GetSize;       //��ȡ����
  TCrabStream_SetSize  SetSize;       //���ó���
  TCrabStream_Position Position;      //��ȡ��ǰλ��
  TCrabStream_Seek     Seek;          //��λ����
  TCrabStream_Read     Read;          //������
  TCrabStream_Write    Write;         //д����
  TCrabStream_Eof      Eof;           //�Ƿ����λ��
  TCrabStream_Free     Free;          //�ͷ���
} TCrabStream, *PCrabStream;

//��ʼ�����ṹ
CrabVoid CrabStream_Init(PCrabStream Stream);

//�ͷ���
CrabUint CrabStream_Free(PCrabStream Stream);

//��ȡ����С
CrabUint CrabStream_GetSize(PCrabStream Stream);

//��������С
CrabUint CrabStream_SetSize(PCrabStream Stream, CrabUint Size);

//��ȡ���ĵ�ǰλ��
CrabUint CrabStream_Position(PCrabStream Stream);

//�����µ���λ��
CrabUint CrabStream_Seek(PCrabStream Stream, CrabUint Offset, CrabInt Origin);
#define CrabStream_SeekAddr(Stream, Addr)  CrabStream_Seek(Stream, Addr, csoBeginning);

//��ȡ������
CrabUint CrabStream_Read(PCrabStream Stream, CrabPoint Buffer, CrabUint Count);

//д��������
CrabUint CrabStream_Write(PCrabStream Stream, CrabPoint Buffer, CrabUint Count);

//�ж����Ƿ��Ѿ�����
CrabBool CrabStream_Eof(PCrabStream Stream);

//�����ж�ȡһ���ֽ�
CrabByte CrabStream_ReadByte(PCrabStream Stream);

//дһ���ֽڵ�����
CrabVoid CrabStream_WriteByte(PCrabStream Stream, CrabByte Value);

//�����ж�ȡһ����
CrabWord CrabStream_ReadWord(PCrabStream Stream);

//дһ���ֵ�����
CrabVoid CrabStream_WriteWord(PCrabStream Stream, CrabWord Value);

//�����ж�ȡһ������
CrabInt CrabStream_ReadInteger(PCrabStream Stream);

//дһ�����ε�����
CrabVoid CrabStream_WriteInteger(PCrabStream Stream, CrabInt Value);

//�����ж�ȡһ��������
CrabBool CrabStream_ReadBoolean(PCrabStream Stream);

//дһ�������͵�����
CrabVoid CrabStream_WriteBoolean(PCrabStream Stream, CrabBool Value);

//�����ж�ȡһ��������
CrabFloat CrabStream_ReadFloat(PCrabStream Stream);

//дһ�������͵�����
CrabVoid CrabStream_WriteFloat(PCrabStream Stream, CrabFloat Value);

//�����ж�ȡһ���ַ�����
CrabString CrabStream_ReadString(PCrabStream Stream, CrabString Result);

//дһ���ַ���������
CrabVoid CrabStream_WriteString(PCrabStream Stream, CrabString Value, CrabByte MaxLength);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE