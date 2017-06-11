/******************** Copyright wisearm.com ************************************
* File Name         : CrabError.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ������Ϣ
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
#include "CrabBaseType.h"
#include "CrabString.h"
#include "CrabErrorMsg.h"

/********************************************************************************
* Function    : CrabErrorMessage()
* Caption     : ���ݴ�����뷵�ش�����Ϣ
*  @Param     : ErrCode - �������
*  @Param     : Result - ������Ϣ(����)
* Return      : CrabString
* Description : .
********************************************************************************/
CrabString  CrabErrorMessage(CrabInt ErrCode, CrabString Result)
{
  if (Result == null)
  {
    return Result;
  }
  
  switch (ErrCode)
  {
    case CrabErrorSuccess:
    {
      CrabStringAssignAnsi(Result, "ִ����ȷ");
      break;
    }
    case CrabErrorNotSupportCommand:
    {
      CrabStringAssignAnsi(Result, "��֧�ֵ�ָ��");
      break;
    }
    case CrabErrorOutOfMemory:
    {
      CrabStringAssignAnsi(Result, "�ڴ����");
      break;
    }
    case  CrabErrorOutOfCodeRom:
    {
      CrabStringAssignAnsi(Result, "����������뷶Χ");
      break;
    }
    case  CrabErrorSetupRegFaild:
    {
      CrabStringAssignAnsi(Result, "��ʼ���Ĵ���ʧ��");
      break;
    }
    case CrabErrorOutOfRegIndex:
    {
      CrabStringAssignAnsi(Result, "�Ĵ���ID������Χ");
      break;
    }
    case CrabErrorOutOfVarMemory:
    {
      CrabStringAssignAnsi(Result, "�ֲ������ڴ泬����Χ");
      break;
    }
    case CrabErrorOutOfObjMemory:
    {
      CrabStringAssignAnsi(Result, "ʵ���ڴ��ѳ�����Χ");
      break;
    }
    case CrabErrorOutOfStackMemory:
    {
      CrabStringAssignAnsi(Result, "ջ�ڴ泬����Χ");
      break;
    }
    case CrabErrorOutOfRegStrMemory:
    {
      CrabStringAssignAnsi(Result, "�Ĵ����ַ���ID������Χ");
      break;
    }
    case CrabErrorInvaildVarType:
    {
      CrabStringAssignAnsi(Result, "��Ч�ı�������");
      break;
    }
    case CrabErrorInvaildVarAddr:
    {
      CrabStringAssignAnsi(Result, "��Ч�ı���ָ���ַ");
      break;
    }
    case CrabErrorInvaildVarHeader:
    {
      CrabStringAssignAnsi(Result, "��Ч�ı�������ͷ");
      break;
    }
    case CrabErrorInvaildCodeAddr:
    {
      CrabStringAssignAnsi(Result, "��Ч�Ĵ����ַ");
      break;
    }
    case CrabErrorInvaildObjAddr:
    {
      CrabStringAssignAnsi(Result, "��Ч��ʵ���������ַ");
      break;
    }
    case CrabErrorInvaildStringCount:
    {
      CrabStringAssignAnsi(Result, "��Ч���ַ�������");
      break;
    }
    case CrabErrorNotEnoughTotalMemory:
    {
      CrabStringAssignAnsi(Result, "û���㹻���ڴ�");
      break;
    }
    case CrabErrorNotEnoughVarMemory:
    {
      CrabStringAssignAnsi(Result, "û���㹻�ľֲ������ڴ�");
      break;
    }
    case CrabErrorNotEnoughStackMemory:
    {
      CrabStringAssignAnsi(Result, "û���㹻��ջ�ڴ�");
      break;
    }
    case  CrabErrorApiFuncNotFound:
    {
      CrabStringAssignAnsi(Result, "��Ч��API��������");
      break;
    }
    case  CrabErrorStackPushFaild:
    {
      CrabStringAssignAnsi(Result, "��ջʧ��");
      break;
    }
    case  CrabErrorStackPopFaild:
    {
      CrabStringAssignAnsi(Result, "��ջʧ��");
      break;
    }
    case  CrabErrorInvaildArrayDim:
    {
      CrabStringAssignAnsi(Result, "��Ч������ά������");
      break;
    }
    case  CrabErrorInvaildObjectSize:
    {
      CrabStringAssignAnsi(Result, "��Ч����ʵ����С");
      break;
    }
    case  CrabErrorInvaildAssignment:
    {
      CrabStringAssignAnsi(Result, "��Ч�ĸ�ֵ��ʽ");
      break;
    }
    case  CrabErrorInvaildFormula:
    {
      CrabStringAssignAnsi(Result, "��Ч�ļ�������");
      break;
    }
    default:
    {
      CrabStringAssignAnsi(Result, "δ֪�Ĵ������");
      break;
    }
  }

  return Result;
}
