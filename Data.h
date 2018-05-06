#pragma once
#include <string>
#include <vector>
using namespace std;

struct Table {
	std::vector<string>line;	//һ�е����ݣ���һ���Ǳ�ͷ
	Table *next;	//��һ��
};

struct Record {
	string tablename;	//�����
	string filename;	//��������ļ���
	Record *next;	//��һ����¼
};

extern Record *Recordhead;