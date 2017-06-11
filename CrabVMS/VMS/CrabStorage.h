/******************** Copyright wisearm.com *********************************
* File Name         : CrabStorage.h
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : .
********************************************************************************/
#ifndef __CRAB_STORAGE__
#define __CRAB_STORAGE__

#include "CrabBaseType.h"
#include "CrabStream.h"
#include "CrabStoreStream.h"

#ifdef  __cplusplus
extern "C" {
#endif  
  
#define CRAB_FLASH_MAX_SIZE   (1024 * 1024)
#define CRAB_EEPROM_MAX_SIZE  (256 * 1024)
  
#define CRAB_SCAN_LAST_FILE   0x01
#define CRAB_SCAN_LAST_SPACE  0x02  
  
typedef struct
{
  CrabUint FileAddr;
  CrabUint FileSize;
} TCrabFileTable, *PCrabFileTable;


extern TCrabStream   FlashStream;
extern TCrabStream   EEpromStream;
extern TCrabStream   CodeStream;

//���������ļ���
CrabBool CrabCreateStoreStream();

//ɨ���ļ����������ҵ��հ�λ�û������ļ�λ��
CrabUint CrabScanFileTable(CrabUint ScanMode, PCrabFileTable FileTable, CrabUint Count);

//�����ļ�������
CrabUint CrabUpdateFileTable(CrabUint Index, PCrabFileTable FileTable);

//�Ӵ洢���������ļ����ݵ��ļ�����
CrabUint CrabLoadFileToCodeStream();
#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE