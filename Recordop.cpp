#include <iostream>
#include <string>
#include <vector>
#include "Data.h"
#include "Recordop.h"

using namespace std;

void Recordop::listTable (Record *h){
	if (h == NULL) return;
	cout << "total:";
	int totalnum = 0;
	for (Record *q = h; q != NULL; q = q->next) {
		totalnum++;
	}
	cout << totalnum << endl;
	for (Record *p = h; p != NULL; p = p->next) {
		cout << p->tablename << ":";
		Table *tmp = new Table;
		tmp = NULL;
		char filename[30] = { '\0' };
		strcpy(filename, p->filename.c_str());
		readTable(tmp,filename);
		int row_num = 0;
		std::vector<string>titles(tmp->line);
		size_t col_num = titles.size();
		while (tmp->next!= NULL) {
			tmp = tmp->next;
			row_num++;
		}
		cout << "(" << col_num << "," << row_num<< ")";
		cout << "[";
		for (vector<string>::iterator iter = titles.begin(); iter!=titles.end(); iter++) {
			if (iter + 1 != titles.end())
				cout << (*iter) << ",";
			else
				cout << (*iter) << "]";
		}
		delete tmp;
		cout << endl;
	}
	return;
}

void Recordop::addTable(Record *&h, string tablename) {
	Record *tmp = new Record;
	tmp->tablename = tablename;
	tmp->filename = tablename + ".txt";
	tmp->next = NULL;

	if (h == NULL) {
		h = tmp;
		return;
	}

	if (h->next == NULL) {
		h->next = tmp;
		return;
	}

	Record *p = h;
	while (p->next!= NULL) {
		p = p->next;
	}
	p->next = tmp;
	return;
}

void Recordop::discardTable(Record *&h, string tablename) {
	if (h == NULL) {
		cout << "No records!" << endl;
		return;
	}
	bool flag = false;

	Record *left = h;
	Record *now = h->next;
	int n = 1;


	for (Record *p = h; p != NULL; p = p->next) {
		if (tablename==p->tablename) {
			flag = true;
			break;
		}
		n++;
		if (!flag&&p->next == NULL) {
			cout << "Not found!" << endl;
			return;
		}
	}

	if (n == 1 && now != NULL) {
		left->tablename = now->tablename;
		left->filename = now->filename;
		left->next = now->next;
		now = NULL;
		delete now;
		if (flag)
		return;
	}

	else if (n == 1 && now == NULL) {
		h = NULL;
		if (flag)
			return;
	}

	for (int i = 2; i < n && now->next != NULL; i++) {
		left = now;
		now = left->next;
	}
	left->next = now->next;
	now = NULL;
	delete now;
	if (flag)
		return;

	if (!flag)
		cout << "Not found!" << endl;
	return;
}
