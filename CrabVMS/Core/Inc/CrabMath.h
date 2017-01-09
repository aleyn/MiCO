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

#ifdef  __cplusplus
extern "C" {
#endif

//ȡ����������������
CrabInt  CrabFloatTrunc(CrabFloat V);

//ȡ��������С���㲿��
CrabFloat  CrabFloatFract(CrabFloat V);

//����������
CrabFloat  CrabFloatMod(CrabFloat V1, CrabFloat V2);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE