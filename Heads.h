#ifndef __HEADS_H
#define __HEADS_H
 
#include <string>
#include <cstring>
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

class File {
public:
	bool readTable(Table *&h,char *filename);
	void writeTable(Table *h,char *filename);
	void readRecord(Record *&h);
	void writeRecord(Record *h);
};

class Tableop {
public:
	void newTable(Table *&h, string title);
	void insertintoTable_columns(Table *&h, string limit,string line);
	void insertintoTable(Table *&h, string line);
	void deleteTable(Table *&h,string limit,string value,int type);
	void deleteTable_all(Table *&h);
	void updateTable_all(Table *&h,string limit, string value);
	void updateTable(Table *&h,string limit, string value,string add_limit,string add_value,int type);
	void showTable_all(Table *h);
	void showTable_all(Table *h,char *filename);
	void showTable_distinct(Table *h, string limit);
	void showTable_distinct(Table *h, string limit,char *filename);
	void showTable_columns(Table *h, string title);
	void showTable_columns(Table *h, string title, char *filename);
	void showTable_sort(Table *&h, string condition, int type);
	void showTable_sort(Table *&h, string condition, int type, char *filename);
	void showTable_columns_limited(Table *h, string title, string add_limit, string add_value, int type);
	void showTable_columns_limited(Table *h, string title, string add_limit, string add_value, int type, char *filename);
	void showTable_all_limited(Table *h, string add_limit, string add_value, int type);
	void showTable_all_limited(Table *h, string add_limit, string add_value, int type, char *filename);
	void showTable_maxminave(Table *h, string condition, int type);
	void showTable_maxminave(Table *h, string condition, int type,char *filename);
};

class Recordop{
public:
	void listTable(Record *h);
	void addTable(Record *&h, string tablename);
	void discardTable(Record *&h, string tablename);
};

#endif
