/******************** Copyright wisearm.com ************************************
* File Name         : CrabMath.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ��ѧ����
********************************************************************************/

#ifndef __CRAB_MATH__
#define __CRAB_MATH__

#include "CrabBaseType.h"

#define CRABCOMPARE_FAILD   0
#define CRABCOMPARE_EQU     0x01
#define CRABCOMPARE_LTN     0x02
#define CRABCOMPARE_GTN     0x04

#define CRABBITOPERAT_BNOT  0x01
#define CRABBITOPERAT_BAND  0x02
#define CRABBITOPERAT_BORR  0x04
#define CRABBITOPERAT_BXOR  0x08


#ifdef  __cplusplus
extern "C" {
#endif

//ȡ����������������
CrabInt  CrabFloatTrunc(CrabFloat V);

//ȡ��������С���㲿��
CrabFloat  CrabFloatFract(CrabFloat V);

//����������
CrabFloat  CrabFloatMod(CrabFloat V1, CrabFloat V2);

//�Ƚ�����
CrabByte  CrabCompareInt(CrabInt V1, CrabInt V2);

//�Ƚ��޷�������
CrabByte  CrabCompareUint(CrabUint V1, CrabUint V2);

//�Ƚϳ�����
CrabByte  CrabCompareLong(CrabLong V1, CrabLong V2);

//�Ƚ��޷��ų�����
CrabByte  CrabCompareULong(CrabULong V1, CrabULong V2);

//�Ƚϸ���
CrabByte  CrabCompareFloat(CrabFloat V1, CrabFloat V2);

//�Ƚ�˫������
CrabByte  CrabCompareDouble(CrabDouble V1, CrabDouble V2);


#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE