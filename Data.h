#pragma once
#include <string>
#include <vector>
using namespace std;

struct Table {
	std::vector<string>line;	//一行的内容，第一行是表头
	Table *next;	//下一行
};

struct Record {
	string tablename;	//表格名
	string filename;	//表格所在文件名
	Record *next;	//下一条记录
};

extern Record *Recordhead;