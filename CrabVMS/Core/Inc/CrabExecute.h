/******************** Copyright wisearm.com ************************************
* File Name         : CrabExecute.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �����ִ�г���
********************************************************************************/

#ifndef __CRAB_EXECUTE__
#define __CRAB_EXECUTE__

#include "CrabBaseType.h"
#include "CrabStream.h"
#include "CrabUtility.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CRAB_APP_OFF              0
#define CRAB_APP_STOPPING         1
#define CRAB_APP_LOADROM          2
#define CRAB_APP_RESET            3
#define CRAB_APP_ERROR            4
#define CRAB_APP_STANDBY          5
#define CRAB_APP_PAUSE            6
#define CRAB_APP_CONTINUE         7
#define CRAB_APP_STEP             8
#define CRAB_APP_RUNNING          9
#define CRAB_APP_EXCEPTION        0xFF

//��������
CrabBool CrabExecute_Create(PCrabConfig Config);

//�ͷŻ���
CrabBool CrabExecute_Destroy();

//��λ����
CrabBool CrabExecute_Clear();

//������
CrabBool CrabExecute_LoadStream(PCrabStream CodeStream, PCrabStream StoreStream);

//��������Ӧ��
CrabBool CrabExecute_Restart();

//ִֹͣ��
CrabBool CrabExecute_Stop();

//��ȡ״̬
CrabBool CrabExecute_Actived();

//��ȡ��ǰָ���ַ
CrabUint CrabExecute_GetCmdAddr();

//��ȡ��ǰ�ļ���λ��
CrabUint CrabExecute_GetAddr();

//�����ļ���λ��
CrabBool CrabExecute_SetAddr(CrabUint Addr);

//Ԥ����ǰָ��
CrabBool CrabExecute_PrepareNextLine();

//ִ�е�ǰ��ָ��
CrabBool CrabExecute_RunCurrentLine();

//����Ƿ����¼������������ת
CrabBool CrabExecute_EventDispatch();

//�׳��������
CrabVoid CrabExecute_RaiseError(CrabInt ErrCode);

//��ȡ�������
CrabUint CrabExecute_GetErrorCode();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE