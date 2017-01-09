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
#include "CrabPlatform.h"

#ifdef  __cplusplus
extern "C" {
#endif

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