/******************** Copyright wisearm.com ************************************
* File Name         : CrabString.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �ַ�������
********************************************************************************/

#ifndef __CRAB_STRING__
#define __CRAB_STRING__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define  CrabStrShortSize   2                                   //���ַ�������ַ����������������޸�
#define  CrabStrLongSize    255                                 //���ַ��������ַ������������Ҫ����Ҹ�

#pragma pack(1)
typedef union
{
  CrabUint   FullData;
  struct
  {
    CrabByte Size;
    CrabByte Len;
    CrabChar Data[CrabStrShortSize];
  };
} TCrabShortString, *PCrabShortString, *CrabShortString;   //�ṹ��ʽ������CrabString����

#pragma pack(1)
typedef struct
{
  CrabByte Size;
  CrabByte Len;
  CrabChar Data[CrabStrLongSize];
} TCrabFullString, *PCrabFullString, *CrabFullString;      //�ṹ��ʽ������CrabString����

#define  CrabStringBuffer(Name, Len)   CrabChar   Name[Len + 2]   //�����ַ������������ʺϾֲ������Զ�����ķ�ʽ

#define  CrabStringCreate(Name, Len) \
         CrabChar    Name##_Buffer[Len + 2]; \
         CrabString  Name = CrabStringAssign(Name##_Buffer, Len, CrabTrue)

//ָ��ĳ��������Ϊ�ַ������ʺϾֲ������Զ�����ķ�ʽ)
CrabString CrabStringAssign(PCrabChar Buffer, CrabByte Len, CrabBool FillZero);

//��ANSI�ַ����н����ַ�������StrΪNullʱ����ֱ�������ַ���
CrabString  CrabStringAlloc(CrabAnsi Str, CrabByte Len);

//������ַ���
CrabString  CrabStringAllocShort();

//����ȫ���ַ���
CrabString  CrabStringAllocFull();

//�ͷ��ַ���
CrabString  CrabStringFree(CrabString Str);

//����ַ���
CrabString  CrabStringClear(CrabString Str);

//�ַ������ƣ�Char��ʽ
CrabString  CrabStringCopyChar(CrabString DstStr, CrabByte DstIdx, CrabChar SrcChar);

//�ַ������ƣ�ANSI��ʽ
CrabString  CrabStringCopyAnsi(CrabString DstStr, CrabByte DstIdx, CrabAnsi SrcStr, CrabByte SrcLen);

//�ַ�������
CrabString  CrabStringCopy(CrabString DstStr, CrabByte DstIdx, CrabString SrcStr);

//�ַ���β����Char��ʽ
CrabString  CrabStringAppendChar(CrabString DstStr, CrabChar SrcChar);

//�ַ���β����ANSI��ʽ
CrabString  CrabStringAppendAnsi(CrabString DstStr, CrabAnsi SrcStr, CrabByte SrcLen);

//�ַ���β��
CrabString  CrabStringAppend(CrabString DstStr, CrabString SrcStr);

//�ַ�������, ANSI��ʽ
CrabString  CrabStringCutAnsi(CrabString DstStr, CrabAnsi SrcStr, CrabByte SrcIdx, CrabByte SrcLen);

//�ַ�������
CrabString  CrabStringCut(CrabString DstStr, CrabString SrcStr, CrabByte SrcIdx, CrabByte SrcLen);

//�ַ�����ANSI�е���
CrabString  CrabStringAssignAnsi(CrabString DstStr, CrabAnsi SrcStr);

//����ͨ�ַ��������IDE�ַ���,ANSIģʽ
CrabUint  CrabStringEncodeAnsi(CrabAnsi DstStr, CrabAnsi SrcStr, CrabByte SrcLen);

//����ͨ�ַ��������IDE�ַ���
CrabString  CrabStringEncode(CrabString DstStr, CrabString SrcStr, CrabBool Clear);

//��IDE�ַ����������ͨ�ַ���,ANSIģʽ
CrabUint  CrabStringDecodeAnsi(CrabAnsi DstStr, CrabAnsi SrcStr, CrabByte SrcLen);

//��IDE�ַ����������ͨ�ַ���
CrabString  CrabStringDecode(CrabString DstStr, CrabString SrcStr, CrabBool Clear);

//�����ַ�����ĳ���Ӵ�
CrabInt CrabStringFind(CrabString Str, CrabString Sub);

//�����ַ�����ĳ���ַ�
CrabInt CrabStringFindC(CrabString Str, CrabChar C);

//��ӡ�ַ���
CrabBool  CrabStringPrint(CrabString Str);

//16�����ַ���תΪ���ֽ�
CrabByte CrabHexToHalfByte(CrabChar HexChar);

//���ֽ�תΪ16�����ַ���
CrabChar CrabHexFromHalfByte(CrabByte Data);

//��16�����ַ���תΪ�޷�������
CrabUint CrabHexToUint(CrabString HexStr, CrabBool IdeMode);

//��16�����ַ���תΪ�з�������
CrabInt CrabHexToInt(CrabString HexStr, CrabBool IdeMode);

//��16�����ַ���תΪ��ͨ�ַ���
CrabString CrabHexToString(CrabString HexStr, CrabString Result);

//����ֵתΪ16�����ַ���
CrabString  CrabHexFromUint(CrabUint Data, CrabUint Digits, CrabBool Clear, CrabString Result);

//��ת����ֵתΪ�ַ�
CrabChar CragEscToChar(CrabString EscStr);

//δ��
CrabString  CrabDateTimeName(CrabString Format, CrabDatetime Datetime, CrabString Result);   //δ��

//�ַ���ת������
CrabBool    CrabStringToBool  (CrabString Value);

//�ַ���ת�޷�������
CrabUint    CrabStringToUint  (CrabString Value);

//�ַ���ת����
CrabInt     CrabStringToInt   (CrabString Value);

//�ַ���ת������
CrabFloat   CrabStringToFloat (CrabString Value);

//�ַ���ת������
CrabDate    CrabStringToDate  (CrabString Value);

//�ַ���תʱ����
CrabTime    CrabStringToTime  (CrabString Value);

//�ַ����Ƿ�������
CrabBool    CrabStringIsInt   (CrabString Value);

//�ַ����Ƿ����޷�������
CrabBool    CrabStringIsUint  (CrabString Value);

//�ַ����Ƿ��Ǹ�����
CrabBool    CrabStringIsFloat (CrabString Value);

//��������תΪ�ַ���
CrabString  CrabStringFromBool  (CrabBool V, CrabBool Clear, CrabString Result);

//������תΪ�ַ���
CrabString  CrabStringFromInt   (CrabInt V, CrabBool Clear, CrabString Result);

//���޷�������תΪ�ַ���
CrabString  CrabStringFromUint    (CrabUint V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromUintIDE (CrabUint V, CrabBool Clear, CrabString Result);

//��������תΪ�ַ���
CrabString  CrabStringFromFloat    (CrabFloat V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromFloatIDE (CrabFloat V, CrabBool Clear, CrabString Result);

//��������תΪ�ַ���
CrabString  CrabStringFromDate     (CrabDate V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromDateIDE  (CrabDate V, CrabBool Clear, CrabString Result);

//��ʱ����תΪ�ַ���
CrabString  CrabStringFromTime     (CrabTime V, CrabBool Clear, CrabString Result);
CrabString  CrabStringFromTimeIDE  (CrabTime V, CrabBool Clear, CrabString Result);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE