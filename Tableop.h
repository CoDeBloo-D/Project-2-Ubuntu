#pragma once
#include "Data.h"
#include <string>
#include <cstring>

class Tableop {
public:
	void newTable(Table *&h, string title);	//新建表格 
	void insertintoTable_limited(Table *&h, string limit,string line);
	void insertintoTable(Table *&h, string line);
	void deleteTable(Table *&h,string limit,string value); //删除表格内部分行(不删除表头)
	void deleteTable_all(Table *&h);			//删除表格内所有行(不删除表头)
	void updateTable_all(Table *&h,string limit, string value);			//更改内容
	void updateTable(Table *&h,string limit, string value,string add_limit,string add_value);				//在指定条件处更改内容
	void showTable_all(Table *h);	//展示整张表格
	void showTable_all_FILE(Table *h,char *filename);	//展示整张表格
	void showTable_distinct(Table *h, string limit);
	void showTable_distinct_FILE(Table *h, string limit,char *filename);
	void showTable_columns(Table *h, string title);
	void showTable_columns_FILE(Table *h, string title, char *filename);
	void showTable_sort(Table *&h, string condition, int type);
	void showTable_sort_FILE(Table *&h, string condition, int type, char *filename);
	void showTable_columns_limited(Table *h, string title,string add_limit, string add_value);
	void showTable_columns_limited_FILE(Table *h, string title, string add_limit, string add_value, char *filename);
	void showTable_all_limited(Table *h, string add_limit, string add_value);
	void showTable_all_limited_FILE(Table *h, string add_limit, string add_value, char *filename);
};