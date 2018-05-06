#pragma once
#include "Data.h"

class File {
public:
	void readTable(Table *&h,char *filename);
	void writeTable(Table *h,char *filename);
	void readRecord(Record *&h);
	void writeRecord(Record *h);
};
