#pragma once
#include <string>
#include "Data.h"
#include "File.h"

class Recordop:public File{
public:
	void listTable(Record *h);
};