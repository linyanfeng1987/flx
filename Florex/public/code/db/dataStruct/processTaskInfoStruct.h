#pragma once
#include "table/TableStruct.h"

class CProcessTaskInfoStruct;
typedef shared_ptr<CProcessTaskInfoStruct> PProcessTaskInfoStruct;
#define newProcessTaskInfoStruct(T) make_shared<CProcessTaskInfoStruct>(T);

class CProcessTaskInfoStruct : public CTableStruct
{
protected:
	CProcessTaskInfoStruct();
public:
	static PProcessTaskInfoStruct instence();
	~CProcessTaskInfoStruct();

	// Ψһid
	static string key_taskId; 
	// ����ʹ�õ�rate�Ǵ�ʱ���
	static string key_rate; 
	// ��ͨrate
	static string key_rateType; 
	static string key_startTime; 
	static string key_endTime; 
	// ����������
	static string key_processTypeName; 
	static string key_paramter; 
	// ����״̬��
	//0�����񱻷���
	//1�������ѷ���
	//2������������
	//3�����������
	//-1������ʧ��
	static string key_status; 
};
