#pragma once
#include "Data.h"

class File {
public:
	void readTable(Table *&h,char *filename);
	void writeTable(Table *h,char *filename);
	void readRecord(Record *&h);
	void writeRecord(Record *h);
	/*��ȡ��� readTable
	��ȡ��¼ readRecord
	ɾ����� deleteTable
	д���� writeTable
	д���¼ writeRecord
	*/
};