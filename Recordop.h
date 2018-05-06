#pragma once
#include <string>
#include "Data.h"
#include "File.h"

class Recordop:public File{
public:
	void listTable(Record *h);	void addTable(Record *&h, string tablename);	void discardTable(Record *&h, string tablename);
};