#pragma once
#include "Data.h"

class File {
public:
	void readTable(Table *&h,char *filename);
	void writeTable(Table *h,char *filename);
	void readRecord(Record *&h);
	void writeRecord(Record *h);
	/*读取表格 readTable
	读取记录 readRecord
	删除表格 deleteTable
	写入表格 writeTable
	写入记录 writeRecord
	*/
};