#pragma once
#include <string>
#include <vector>
using namespace std;

struct Table {
	std::vector<string>line;
	Table *next;
};

struct Record {
	string tablename;
	string filename;
	Record *next;
};

extern Record *Recordhead;
