/******************** Copyright wisearm.com ************************************
* File Name         : CrabExtern.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API����������
********************************************************************************/

#ifndef __CRAB_EXTERN__
#define __CRAB_EXTERN__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CrabUserApiBase      0x000010
#define CrabExtern_RegisterApi(Name, Addr)   CrabExtern_RegisterFuncName(Name, __ref Addr)

//����API�������ýӿ�
typedef crabapi(*TCrabApiFunc)    ();
typedef crabapi(*TCrabEventFunc)  (CrabBool State);
typedef crabapi(*TCrabInput)      (CrabUint Type, CrabAnsi Buffer, PCrabUint Length);
typedef crabapi(*TCrabPrint)      (CrabAnsi Text, CrabUint Length);
typedef crabapi(*TCrabDelay)      (CrabUint MSec);

#pragma pack(1)
typedef struct
{
  TCrabApiFunc   getClock;   //��ʱ��
  TCrabApiFunc   setClock;   //дʱ��
  TCrabApiFunc   getBus;     //������
  TCrabApiFunc   setBus;     //д����
} TCrabStaticPort, *PCrabStaticPort;

#pragma pack(1)
typedef struct
{
  TCrabEventFunc    EventIntr;
  TCrabInput        Input;
  TCrabPrint        Print;
  TCrabDelay        Delay;
} TCrabStaticApi, *PCrabStaticApi;

extern TCrabStaticPort      CrabStaticPort;
extern TCrabStaticApi       CrabStaticApi;

//��ӡ��ʽ�ַ������ն���ʾ��
CrabVoid CrabExtern_PrintFormat(CrabAnsi Format, ...);

//��ӡ�ַ������ն���ʾ��
CrabVoid CrabExtern_PrintString(CrabString Text);

//ע��API����
CrabBool CrabExtern_RegisterFunction(CrabWord ApiIndex, TCrabApiFunc ApiAddr);

//ע��API����
CrabBool CrabExtern_UnregisterFunction(CrabWord ApiIndex);

//ע��API���������Ʒ�ʽ
CrabBool CrabExtern_RegisterFuncName(const CrabAnsi ApiName, TCrabApiFunc ApiAddr);

//����API��������λ��
CrabBool CrabExtern_FindFuncIndex(const CrabAnsi ApiName, CrabWord __var ApiIndex, CrabBool IgnoreUsed);

//����API������ַ
CrabUint CrabExtern_GetFuncAddr(CrabWord ApiIndex);

//����API��������
CrabBool CrabExtern_LoadFuncName(CrabWord ApiIndex, CrabString ApiName);

//��ȡ��������
CrabUint CrabExtern_GetParamCount();

//��ȡ�˿ڵ�ַ
CrabUint CrabExtern_GetPortAddr();

//�жϲ����Ƿ�ΪNull
CrabUint CrabExtern_ParamIsNull(CrabUint ParamIndex);

//�жϲ����Ƿ�ΪNull
CrabUint CrabExtern_ParamIsString(CrabUint ParamIndex);

//��ȡ�����Ͳ���
CrabBool CrabExtern_GetBoolParam(CrabUint ParamIndex);

//��ȡ���Ͳ���
CrabInt  CrabExtern_GetIntParam(CrabUint ParamIndex);

//��ȡ�޷������Ͳ���
CrabUint CrabExtern_GetUintParam(CrabUint ParamIndex);

//��ȡ�����Ͳ���
CrabDate CrabExtern_GetDateParam(CrabUint ParamIndex);

//��ȡʱ���Ͳ���
CrabTime CrabExtern_GetTimeParam(CrabUint ParamIndex);

//��ȡ�����Ͳ���
CrabFloat  CrabExtern_GetFloatParam(CrabUint ParamIndex);

//��ȡ�ַ����Ͳ���
CrabString CrabExtern_GetStringParam(CrabUint ParamIndex);

//������ת��Ϊ�ַ�����
CrabString CrabExtern_ConvertParamToString(CrabUint ParamIndex, CrabString Result);

//ȡ����ʱ�ַ���������
CrabString CrabExtern_GetTempString();

//���ز�����
CrabBool CrabExtern_ReturnBoolValue(CrabBool ParamIndex);

//���ؿ�ֵ
CrabBool CrabExtern_ReturnNullValue();

//��������
CrabBool CrabExtern_ReturnIntValue(CrabInt Result);

//�����޷�������
CrabBool CrabExtern_ReturnUintValue(CrabUint Result);

//����������
CrabBool CrabExtern_ReturnDateValue(CrabDate Result);

//����ʱ����
CrabBool CrabExtern_ReturnTimeValue(CrabTime Result);

//���ظ�����
CrabBool CrabExtern_ReturnFloatValue(CrabFloat Result);

//�����ַ�����
CrabBool CrabExtern_ReturnStringValue(CrabString Result);

//ȡ�ú������ؼĴ������ַ���������
CrabString CrabExtern_GetReturnString();



#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE