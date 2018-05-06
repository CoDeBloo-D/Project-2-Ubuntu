#pragma once
#include "Data.h"
#include <string>
#include <cstring>

class Tableop {
public:
	void newTable(Table *&h, string title);	
	void insertintoTable_limited(Table *&h, string limit,string line);
	void insertintoTable(Table *&h, string line);
	void deleteTable(Table *&h,string limit,string value); 
	void deleteTable_all(Table *&h);		
	void updateTable_all(Table *&h,string limit, string value);			
	void updateTable(Table *&h,string limit, string value,string add_limit,string add_value);				
	void showTable_all(Table *h);
	void showTable_all_FILE(Table *h,char *filename);
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
