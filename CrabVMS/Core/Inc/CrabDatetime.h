/******************** Copyright wisearm.com ************************************
* File Name         : CrabDatetime.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ����ʱ�亯��
********************************************************************************/

#ifndef __CRAB_DATETIME__
#define __CRAB_DATETIME__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

//ȡ�ù�Ԫ������ĳһ��������ܺ�.
CrabUint  CrabDate_GetYearSumDay(CrabWord Year);

//ȡ��һ���д�1�µ�ָ���·ݵ������ܺ�.
CrabUint  CrabDate_GetMonthSumDay(CrabWord Year, CrabWord Month);

//ȡ��һ����ĳ���·ݵ�������
CrabUint  CrabDate_GetMonthDay(CrabWord Year, CrabWord Month);

//���������ڱ�������ڸ�ʽ
CrabDate  CrabDate_Encode(CrabWord Year, CrabByte Month, CrabByte Day);

//�����ڸ�ʽ����ɵ�������
CrabBool  CrabDate_Decode(CrabDate Date, CrabWord __var wYear, CrabByte __var bMonth, CrabByte __var bDay);

//���ڸ�ʽתΪ����
CrabDate  CrabDate_Packed(TCrabDate Date);

//����תΪ������
TCrabDate CrabDate_Unpacked(CrabUint Date);

//������ʱ������ʱ���ʽ
CrabTime  CrabTime_Encode(CrabByte Hour, CrabByte Min, CrabByte Sec, CrabWord MSec);

//��ʱ���ʽ����ɵ���ʱ��
CrabBool  CrabTime_Decode(CrabTime Time, CrabByte __var Hour, CrabByte __var Min, CrabByte __var Sec, CrabWord __var MSec);

//ʱ����תΪ����
CrabTime  CrabTime_Packed(TCrabTime Time);

//����תΪʱ����
TCrabTime CrabTime_Unpacked(CrabTime Time);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE