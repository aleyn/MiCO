/******************** Copyright wisearm.com ************************************
* File Name         : CrabBaseType.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ��������
********************************************************************************/
#ifndef __CRAB_BASE_TYPE__
#define __CRAB_BASE_TYPE__

//#include "xxx.h"

#ifdef  __cplusplus
extern "C" {
#endif

//�ض���
#define  crabapi   void                //����
#define  __var     *                   //�������
#define  __ref     &                   //������ַ
#define  nil       ((void *)0)         //��ָ��
#define  null      ((void *)0)         //��ָ��
#define  nullstr   ((char *)0)         //���ַ���
#define  not       !                   //�߼���
#define  and       &&                  //�߼���
#define  or        ||                  //�߼���

#define  False     0                   //�߼���
#define  True      !False              //�߼���

#define  CrabNull           null              //��ָ��
#define  CrabNullString     (CrabString)(0)   //���ַ���
#define  CrabTrue           0x00000001        //True  - CrabBool ��ֵ
#define  CrabFalse          0x00000000        //False - CrabBool ��ֵ
  
#ifdef  __ICCARM__  
#define __flash _Pragma("location=\".rodata\"")
#define __cache _Pragma("location=\".ccmram\"")
#define __ram   _Pragma("location=\".data\"")
#else
#define __flash
#define __cache
#define __ram
#endif

//��������
typedef          char  CrabChar;      //�ַ���
typedef unsigned char  CrabByte;      //���ֽ�
typedef unsigned short CrabWord;      //˫�ֽ�
typedef unsigned int   CrabUint;      //���ֽڣ��޷�������
typedef unsigned long  CrabULong;     //���ֽڣ��޷��ų�����
typedef unsigned int   CrabBool;      //������
typedef          int   CrabInt;       //�з�������
typedef          long  CrabLong;      //�з��ų�����
typedef          float CrabFloat;     //������
typedef unsigned int   CrabUID;       //Ωһ��ֵ
typedef unsigned int   CrabHandle;    //�����
typedef          void  CrabVoid;      //������

typedef CrabChar      *PCrabChar;
typedef CrabByte      *PCrabByte;
typedef CrabWord      *PCrabWord;
typedef CrabUint      *PCrabUint;
typedef CrabBool      *PCrabBool;
typedef CrabFloat     *PCrabFloat;
typedef CrabVoid      *CrabPoint;

typedef CrabChar      *CrabAnsi; //C����ȱʡ�ַ�������

#pragma pack(1)
//������
typedef CrabUint      CrabDate;
typedef union
{
  CrabDate            Date;
  struct
  {
    CrabWord          Year;
    CrabByte          Month;
    CrabByte          Day;
  };
} TCrabDate, *PCrabDate;   //������

#pragma pack(1)
//ʱ����
typedef CrabUint      CrabTime;
typedef union
{
  CrabTime          Time;
  struct
  {
    CrabByte        Hour;
    CrabByte        Min;
  };
  struct
  {
    CrabUint        Res  :16;
    CrabUint        Sec  :6;
    CrabUint        MSec :10;
  };
} TCrabTime, *PCrabTime;   //ʱ����

//����ʱ����
typedef union
{
  CrabDate       Date;
  CrabTime       Time;
} TCrabDatetime, *PCrabDatetime, CrabDatetime;  //����ʱ����

//�ַ����ͣ���ϵͳ�ã�ʵ�������ڴ��СΪԭʼ����+3;
typedef struct
{
  CrabByte Size;                           //�ַ����ڴ��С;
  CrabByte Len;                            //�ַ�����ǰ���ȣ�Len <= Size;
  CrabChar Data[0];                        //�ַ������ݣ�(���һ���ַ�Ϊ\0������ANSI C�ķ�ʽ)
} TCrabString, *PCrabString, *CrabString;  //�ַ�����

//˫�ֽڵ�ַ
typedef union
{
  CrabWord Addr;
  CrabByte Addrs[2];
} TCrabUnionWord;               //˫�ֽڹ���

//���ֽڵ�ַ
typedef union
{
  CrabByte Values[3];          //����ֵ�����ֽ�
  struct
  {
    CrabWord LowValue;         //��λֵ��˫�ֽ�
    CrabByte HighValue;        //��λֵ�����ֽ�
  };
} TCrabThree, TCrabCodeAddr;   //���ֽڵ�ַ

//�Ľ�������
typedef union
{
  CrabUint     FullValue;      //�ϲ�ֵ���޷�������
  CrabInt      IntValue;       //�з�������
  CrabByte     Values[4];      //����ֵ�����ֽ�
  struct
  {
    CrabWord   LowValue;       //��λֵ��˫�ֽ�
    CrabWord   HighValue;      //��λֵ��˫�ֽ�
  };
  struct  
  {
    CrabByte   ByteValue0;
    CrabByte   ByteValue1;
    CrabByte   ByteValue2;
    CrabByte   ByteValue3;
  };
} TCrabUnion, CrabUnion;                  //�Ľ�������

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE