/******************** Copyright wisearm.com *********************************
* File Name         : CrabStoreStream.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : .
********************************************************************************/
#ifndef __CRAB_STORESTREAM__
#define __CRAB_STORESTREAM__

#include "CrabBaseType.h"
#include "CrabStream.h"

#ifdef  __cplusplus
extern "C" {
#endif  

#define CRAB_STORE_TYPE_FLASH      1
#define CRAB_STORE_TYPE_EEPROM     2
  
#define CRAB_FLASH_SECTION_SIZE    4096   // = (4 * 1024)
#define CRAB_FLASH_SECTION_COUNT   256
  
#pragma pack(1)
typedef struct
{
  CrabUint  Type;
  CrabUint  Offset;
  CrabUint  Size;
  CrabUint  Addr;
} TCrabStoreInfo, *PCrabStoreInfo, *CrabStoreInfo;  
  
//����FLASH����EEPROM��
CrabUint CrabStoreStream_Create(PCrabStream Stream, CrabStoreInfo StoreInfo);

//��������Ϣ
CrabUint CrabStoreStream_Update(PCrabStream Stream, CrabUint Offset, CrabUint Size);

//�򿪻����洢����д����
CrabUint CrabStoreStream_WriteProtect(PCrabStream Stream, CrabBool State);

//ɾ�����е�����
CrabUint CrabStoreStream_EarseAll(PCrabStream Stream);

//ɾ����������
CrabUint CrabStoreStream_EarseSector(PCrabStream Stream, CrabUint SecAddr, CrabUint Count);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE