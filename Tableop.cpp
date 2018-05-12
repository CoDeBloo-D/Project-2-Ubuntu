#include <iostream>
#include <string>
#include <cstring>
#include <vector> 
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Heads.h"

using namespace std;

void Tableop::newTable(Table *&h, string title) {
	if (h != NULL) {
		Table *del = new Table;
		del = h;
		h = h->next;
		delete del;
	}

	vector<string> titles;
	stringstream sstr(title);
	string token;
	vector<string>::iterator iter;
	while (getline(sstr, token, ','))
	{
		titles.push_back(token);
	}

	Table *tmp = new Table;
	tmp->next = NULL;

	for (iter=titles.begin(); iter!=titles.end(); iter++) {
		tmp->line.push_back(*iter);
	}
	
	h = tmp;
}

void Tableop::insertintoTable(Table *&h, string line) {
	vector<string> words;
	stringstream sstr(line);
	string token;
	vector<string>::iterator iter;
	while (getline(sstr, token, ','))
	{
		words.push_back(token);
	}
	size_t col_num = h->line.size();
	if(words.size()>col_num){
		cout<<"TOO MUCH DATA!"<<endl;
		return;
	} 
	Table *n = new Table;
	n->next = NULL;
	for (iter = words.begin(); iter != words.end(); iter++) {
		n->line.push_back((*iter));
	}

	while (n->line.size() != col_num)
		n->line.push_back("\t");
	Table *r = h;
	while (r->next != NULL)
		r = r->next;
	r->next = n;
	return;
}

void Tableop::insertintoTable_columns(Table *&h, string limit, string line) {
	vector<string> limits;
	vector<string> words;
	vector<string> titles(h->line);

	stringstream sstr_1(limit);
	string token;
	while (getline(sstr_1, token, ','))
	{
		limits.push_back(token);
	}

	stringstream sstr_2(line);
	string cell;
	while (getline(sstr_2, cell, ','))
	{
		words.push_back(cell);
	}
	
	if(limits.size()>titles.size()||limits.size()<words.size()){
		cout<<"TOO MUCH VALUES OR TOO MUCH COLUMNS!"<<endl;
		return;
	}
	bool index[30];
	int i = 0;
	for (int i = 0; i < 30; i++)
		index[i] = false;

	i = 0;
	for (vector<string>::iterator iter = titles.begin(); iter != titles.end(); iter++) {
		for (vector<string>::iterator iter_2 = limits.begin(); iter_2 != limits.end(); iter_2++) {
			if ((*iter) == (*iter_2))
				index[i] = true;
		}
		i++;
	}

	size_t col_num = h->line.size();
	Table *n = new Table;
	n->next = NULL;
	for (size_t j = 0; j < col_num; j++) {
		vector<string>::iterator iter = words.begin();
		if (index[j]) {
			index[j] = false;
			n->line.push_back(*iter);
			words.erase(words.begin());
		}
		else
			n->line.push_back("\t");
	}
	Table *r = h;
	while (r->next != NULL)
		r = r->next;
	r->next = n;
	return;
}

void Tableop::deleteTable(Table *&h, string limit, string value,int type) {
	vector<string> titles(h->line);
	size_t col_num = h->line.size();
	size_t index = -1;
	for (size_t j = 0; j < col_num; j++) {
		if (titles[j] == limit) {
			index = j;
			break;
		}
	}

	if (index == -1) {
		cout << "NOT MATCHED!" << endl;
		return;
	}
	Table *pre = h;
	Table *now = pre->next;
	if (pre->next == NULL) return;
	while ( now != NULL) {
		if (type == 0) {
				if (now->line[index] == value) {
					pre->next = now->next;
					now = now->next;
				}
				else {
					now = now->next;
					pre = pre->next;
				}
		}
		else if (type == -1) {
				if (now->line[index] <= value) {
					pre->next = now->next;
					now = now->next;
				}
				else {
					now = now->next;
					pre = pre->next;
				}
		}

		else if (type == 1) {
				if (now->line[index] >= value) {
					pre->next = now->next;
					now = now->next;
				}
				else {
					now = now->next;
					pre = pre->next;
				}
		}

		else if (type == -2) {
				if (now->line[index] < value) {
					pre->next = now->next;
					now = now->next;
				}
				else {
					now = now->next;
					pre = pre->next;
				}
		}

		else if (type == 2) {
				if (now->line[index] > value) {
					pre->next = now->next;
					now = now->next;
				}
				else {
					now = now->next;
					pre = pre->next;
				}
		}
		else if (type == 3) {
				if (now->line[index]!= value) {
					pre->next = now->next;
					now = now->next;
				}
				else {
					now = now->next;
					pre = pre->next;
				}
		}
	}
	return;
}

void Tableop::deleteTable_all(Table *&h) {
	Table *p = h;
	while (p->next != NULL) {
		Table *del = p->next;
		p->next = del->next;
		delete del;
	}
	return;
}

void Tableop::updateTable_all(Table *&h,string limit, string value) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	vector<string> limits;
	vector<string> values;
	stringstream sstr1(limit);
	stringstream sstr2(value);

	string token;
	while (getline(sstr1, token, ','))
	{
		limits.push_back(token);
	}

	string cell;
	while (getline(sstr2, cell, ','))
	{
		values.push_back(cell);
	}

	bool index[30];
	int i = 0;
	for (i; i < 30; i++) {
		index[i] = false;
	}


	for (i = 0;i<(int)col_num; i++) {
		for (int k = 0; k < (int)limits.size(); k++) {
			if (limits[k] == titles[i]) {
				index[i] = true;
				break;
			}
		}
	}

	
	for (Table *p = h->next; p != NULL; p = p->next) {
		vector<string> values_copy(values);
		for (size_t j = 0; j < col_num; j++) {
			vector<string>::iterator iter = values_copy.begin();
			if (index[j]) {
				p->line[j] = (*iter);
				values_copy.erase(values_copy.begin());
			}
		}
	}

	return;
}

void Tableop::updateTable(Table *&h, string limit, string value, string add_limit, string add_value,int type) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	vector<string> limits;
	vector<string> values;
	stringstream sstr1(limit);
	stringstream sstr2(value);

	string token;
	while (getline(sstr1, token, ','))
	{
		limits.push_back(token);
	}

	string cell;
	while (getline(sstr2, cell, ','))
	{
		values.push_back(cell);
	}

	bool index[30];
	int condition = -1;
	int i = 0;
	for (i; i < (int)col_num; i++) {
		index[i] = false;
	}


	for (i = 0; i<(int)col_num; i++) {
		for (int k = 0; k < (int)limits.size(); k++) {
			if (limits[k] == titles[i]) {
				index[i] = true;
				break;
			}
		}
	}

	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == add_limit) {
			condition = i;
			break;
		}
	}

	//cout << condition << endl;

	for (Table *p = h->next; p != NULL; p = p->next) {
		vector<string> test(p->line);
		if (type == 0) {
			if (test[condition] == add_value) {
				vector<string> values_copy(values);
				for (size_t j = 0; j < col_num; j++) {
					vector<string>::iterator iter = values_copy.begin();
					if (index[j]) {
						p->line[j] = (*iter);
						values_copy.erase(values_copy.begin());
					}
				}
			}
		}

		else if (type == -1) {
			if (test[condition] <= add_value){
				vector<string> values_copy(values);
				for (size_t j = 0; j < col_num; j++) {
					vector<string>::iterator iter = values_copy.begin();
					if (index[j]) {
						p->line[j] = (*iter);
						values_copy.erase(values_copy.begin());
					}
				}
			}
		}

		else if (type == 1) {
			if (test[condition] >= add_value) {
				vector<string> values_copy(values);
				for (size_t j = 0; j < col_num; j++) {
					vector<string>::iterator iter = values_copy.begin();
					if (index[j]) {
						p->line[j] = (*iter);
						values_copy.erase(values_copy.begin());
					}
				}
			}
		}

		else if (type == -2) {
			if (test[condition] < add_value) {
				vector<string> values_copy(values);
				for (size_t j = 0; j < col_num; j++) {
					vector<string>::iterator iter = values_copy.begin();
					if (index[j]) {
						p->line[j] = (*iter);
						values_copy.erase(values_copy.begin());
					}
				}
			}
		}

		else if (type == 2) {
			if (test[condition] > add_value) {
				vector<string> values_copy(values);
				for (size_t j = 0; j < col_num; j++) {
					vector<string>::iterator iter = values_copy.begin();
					if (index[j]) {
						p->line[j] = (*iter);
						values_copy.erase(values_copy.begin());
					}
				}
			}
		}

		else if (type == 3) {
			if (test[condition] != add_value) {
				vector<string> values_copy(values);
				for (size_t j = 0; j < col_num; j++) {
					vector<string>::iterator iter = values_copy.begin();
					if (index[j]) {
						p->line[j] = (*iter);
						values_copy.erase(values_copy.begin());
					}
				}
			}
		}
	}
	return;
}

void Tableop::showTable_all(Table *h) {
	int id = 0;
	size_t width[30];
	int i = 0;
	for (int j = 0; j < 30; j++)
		width[j] = 0;

	for (Table *p = h; p != NULL; p = p->next) {
		i = 0;
		for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
			width[i] = width[i] >(*iter).length() ? width[i] : (*iter).length();
			i++;
		}
	}

	for (Table *p = h; p != NULL; p = p->next) {
		i = 0;
		if (id == 0)
			cout << setw(6) << setiosflags(ios::left) << "ID";
		else
			cout << setw(6) << setiosflags(ios::left) << id;
		for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
			cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
			i++;
		}
		cout << endl;
		id++;
	}
	return;
}

void Tableop::showTable_all(Table *h, char *filename) {
	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	for (Table *p = h; p != NULL; p = p->next) {
		for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
			fout<< (*iter)<<" ";
		}
		fout << endl;
	}
	fout.close();
	fout.clear();
	return;
}

void Tableop::showTable_distinct(Table *h, string limit) {
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	int condition = -1;
	for (size_t j = 0; j < titles.size(); j++) {
		if (titles[j] == limit)
			condition = j;
	}
	vector<string> show;
	show.push_back(titles[condition]);
	for (Table *p = h; p != NULL; p = p->next) {
		if (p->line.size() == 0) break;
		bool flag = true;
		for (size_t i = 0; i < show.size(); i++) {
			if (p->line[condition] == show[i]) {
				flag = false;
				break;
			}
		}
		if (flag)
			show.push_back(p->line[condition]);
	}

	int id = 0;
	for (Table *p = h; p != NULL; p = p->next) {
		vector<string>::iterator iter =show.begin();
		if (show.size() == 0)
			break;
		if (id == 0) {
			cout << setw(6) << setiosflags(ios::left) << "ID";
			cout << setw(6) << setiosflags(ios::left) << (*iter);
			show.erase(show.begin());
		}
		else {
			cout << setw(6) << setiosflags(ios::left) << id;
			cout << setw(6) << setiosflags(ios::left) << (*iter);
			show.erase(show.begin());
		}
		cout << endl;
		id++;
	}
}

void Tableop::showTable_distinct(Table *h, string limit, char *filename) {
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	int condition = -1;
	for (size_t j = 0; j < titles.size(); j++) {
		if (titles[j] == limit)
			condition = j;
	}
	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	vector<string> show;
	show.push_back(titles[condition]);
	for (Table *p = h; p != NULL; p = p->next) {
		if (p->line.size() == 0) break;
		bool flag = true;
		for (size_t i = 0; i < show.size(); i++) {
			if (p->line[condition] == show[i]) {
				flag = false;
				break;
			}
		}
		if (flag)
			show.push_back(p->line[condition]);
	}

	for (Table *p = h; p != NULL; p = p->next) {
		vector<string>::iterator iter = show.begin();
		if (show.size() == 0)
			break;
		fout<< (*iter)<<" ";
		show.erase(show.begin());
		fout << endl;
	}
	fout.close();
	fout.clear();
}

void Tableop::showTable_columns(Table *h, string title) {
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	vector<string> limits;
	stringstream sstr(title);
	string token;
	vector<string>::iterator iter;
	while (getline(sstr, token, ','))
	{
		limits.push_back(token);
	}

	size_t width[30];
	for (int j = 0; j < 30; j++)
		width[j] = 0;
	int i = 0;
	for (Table *q = h; q != NULL; q = q->next) {
		i = 0;
		for (vector<string>::iterator iter = q->line.begin(); iter != q->line.end(); iter++) {
			width[i] = width[i] >(*iter).length() ? width[i] : (*iter).length();
			i++;
		}
	}

	bool index[30];
	for (i=0; i < 30; i++) {
		index[i] = false;
	}

	for (i = 0; i<(int)col_num; i++) {
		for (int k = 0; k < (int)limits.size(); k++) {
			if (limits[k] == titles[i]) {
				index[i] = true;
				break;
			}
		}
	}

	int id = 0;
	for (Table *p = h; p != NULL; p = p->next) {
		if (id == 0) {
			cout << setw(6) << setiosflags(ios::left) << "ID";
		}
		else {
			cout << setw(6) << setiosflags(ios::left) << id;
		}
		for (size_t j = 0; j < col_num; j++) {
			if(index[j])
				cout << setw(width[j] + 1) << setiosflags(ios::left) <<p->line[j];
		}
		cout << endl;
		id++;
	}
	return;
}

void Tableop::showTable_columns(Table *h, string title, char *filename) {
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	vector<string> limits;
	stringstream sstr(title);
	string token;
	vector<string>::iterator iter;
	while (getline(sstr, token, ','))
	{
		limits.push_back(token);
	}

	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	int i = 0;
	bool index[30];
	for (i = 0; i < 30; i++) {
		index[i] = false;
	}

	for (i = 0; i<(int)col_num; i++) {
		for (int k = 0; k < (int)limits.size(); k++) {
			if (limits[k] == titles[i]) {
				index[i] = true;
				break;
			}
		}
	}

	for (Table *p = h; p != NULL; p = p->next) {
		for (size_t j = 0; j < col_num; j++) {
			if (index[j])
				fout << p->line[j]<<" ";
		}
		fout << endl;
	}
	fout.close();
	fout.clear();
	return;
}

void Tableop::showTable_sort(Table *&h, string condition, int type) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();

	int conindex = -1;
	int i = 0;

	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == condition) {
			conindex = i;
			break;
		}
	}

	size_t width[30];
	for (int j = 0; j < 30; j++)
		width[j] = 0;

	for (Table *w = h; w != NULL; w = w->next) {
		i = 0;
		for (vector<string>::iterator iter = w->line.begin(); iter != w->line.end(); iter++) {
			width[i] = width[i] >(*iter).length() ? width[i] : (*iter).length();
			i++;
		}
	}

	if (type == 1) {
		Table *p = new Table;
		p = h->next;
		Table *q = new Table;
		q = p->next;
		while( p->next != NULL) {
			q = p->next;
			while(q != NULL) {
				if (p->line[conindex] > q->line[conindex]) {
					vector<string> tmp(p->line);
					p->line.assign(q->line.begin(), q->line.end());
					q->line.assign(tmp.begin(), tmp.end());
				}
				q = q->next;
			}
			p = p->next;
		}
	}

	else if (type == 0) {
		Table *p = new Table;
		p = h->next;
		Table *q = new Table;
		q = p->next;
		while (p->next != NULL) {
			q = p->next;
			while (q != NULL) {
				if (p->line[conindex] < q->line[conindex]) {
					vector<string> tmp(p->line);
					p->line.assign(q->line.begin(), q->line.end());
					q->line.assign(tmp.begin(), tmp.end());
				}
				q = q->next;
			}
			p = p->next;
		}
	}

	int id = 0;
	for (Table *t = h; t != NULL; t = t->next) {
		if (t->line.size() == 0) break;
		i = 0;
		if (id == 0)
			cout << setw(6) << setiosflags(ios::left) << "ID";
		else
			cout << setw(6) << setiosflags(ios::left) << id;
		for (vector<string>::iterator iter = t->line.begin(); iter != t->line.end(); iter++) {
			cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
			i++;
		}
		cout << endl;
		id++;
	}
}

void Tableop::showTable_sort(Table *&h, string condition, int type, char *filename) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();

	int conindex = -1;
	int i = 0;

	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == condition) {
			conindex = i;
			break;
		}
	}
	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	if (type == 1) {
		Table *p = new Table;
		p = h->next;
		Table *q = new Table;
		q = p->next;
		while (p->next != NULL) {
			q = p->next;
			while (q != NULL) {
				if (p->line[conindex] > q->line[conindex]) {
					vector<string> tmp(p->line);
					p->line.assign(q->line.begin(), q->line.end());
					q->line.assign(tmp.begin(), tmp.end());
				}
				q = q->next;
			}
			p = p->next;
		}
	}

	else if (type == 0) {
		Table *p = new Table;
		p = h->next;
		Table *q = new Table;
		q = p->next;
		while (p->next != NULL) {
			q = p->next;
			while (q != NULL) {
				if (p->line[conindex] < q->line[conindex]) {
					vector<string> tmp(p->line);
					p->line.assign(q->line.begin(), q->line.end());
					q->line.assign(tmp.begin(), tmp.end());
				}
				q = q->next;
			}
			p = p->next;
		}
	}

	for (Table *t = h; t != NULL; t = t->next) {
		if (t->line.size() == 0) break;
		for (vector<string>::iterator iter = t->line.begin(); iter != t->line.end(); iter++) {
			fout << (*iter)<<" ";
			i++;
		}
		fout << endl;
	}
	fout.close();
	fout.clear();
}

void Tableop::showTable_columns_limited(Table *h, string title, string add_limit, string add_value, int type){
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();

	vector<string> limits;
	stringstream sstr(title);
	string token;
	vector<string>::iterator iter;
	while (getline(sstr, token, ','))
	{
		limits.push_back(token);
	}

	size_t width[30];
	for (int j = 0; j < 30; j++)
		width[j] = 0;
	int i = 0;
	for (Table *q = h; q != NULL; q = q->next) {
		i = 0;
		for (vector<string>::iterator iter = q->line.begin(); iter != q->line.end(); iter++) {
			width[i] = width[i] >(*iter).length() ? width[i] : (*iter).length();
			i++;
		}
	}

	bool index[30];
	for (i = 0; i < 30; i++) {
		index[i] = false;
	}

	for (i = 0; i<(int)col_num; i++) {
		for (int k = 0; k < (int)limits.size(); k++) {
			if (limits[k] == titles[i]) {
				index[i] = true;
				break;
			}
		}
	}
	int condition = -1;
	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == add_limit) {
			condition = i;
			break;
		}
	}
	int id = 0;
	cout << setw(6) << setiosflags(ios::left) << "ID";
	id++;
	for (size_t j = 0; j < col_num; j++) {
		if (index[j])
			cout << setw(width[j] + 1) << setiosflags(ios::left) << titles[j];
	}
	cout << endl;
	for (Table *p = h->next; p != NULL; p = p->next) {
		if (type == 0) {
			if (p->line[condition] == add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						cout << setw(width[j] + 1) << setiosflags(ios::left) << p->line[j];
				}
				cout << endl;
				id++;
			}
		}

		else if (type == -1) {
			if (p->line[condition] <= add_value){
				cout << setw(6) << setiosflags(ios::left) << id;
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						cout << setw(width[j] + 1) << setiosflags(ios::left) << p->line[j];
				}
				cout << endl;
				id++;
			}
		}

		else if (type == 1) {
			if (p->line[condition] >= add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						cout << setw(width[j] + 1) << setiosflags(ios::left) << p->line[j];
				}
				cout << endl;
				id++;
			}
		}

		else if (type == -2) {
			if (p->line[condition] < add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						cout << setw(width[j] + 1) << setiosflags(ios::left) << p->line[j];
				}
				cout << endl;
				id++;
			}
		}

		else if (type == 2) {
			if (p->line[condition] > add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						cout << setw(width[j] + 1) << setiosflags(ios::left) << p->line[j];
				}
				cout << endl;
				id++;
			}
		}

		else if (type == 3) {
			if (p->line[condition] != add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						cout << setw(width[j] + 1) << setiosflags(ios::left) << p->line[j];
				}
				cout << endl;
				id++;
			}
		}
	}
	return;
}

void Tableop::showTable_columns_limited(Table *h, string title, string add_limit, string add_value, int type, char *filename) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();

	vector<string> limits;
	stringstream sstr(title);
	string token;
	vector<string>::iterator iter;
	while (getline(sstr, token, ','))
	{
		limits.push_back(token);
	}

	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	int i;
	bool index[30];
	for (i = 0; i < 30; i++) {
		index[i] = false;
	}

	for (i = 0; i<(int)col_num; i++) {
		for (int k = 0; k < (int)limits.size(); k++) {
			if (limits[k] == titles[i]) {
				index[i] = true;
				break;
			}
		}
	}
	int condition = -1;
	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == add_limit) {
			condition = i;
			break;
		}
	}
	for (size_t j = 0; j < col_num; j++) {
		if (index[j])
			fout << titles[j]<<" ";
	}
	fout << endl;
	for (Table *p= h->next; p != NULL; p = p->next) {
		if (type == 0) {
			if (p->line[condition] == add_value) {
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						fout << p->line[j] << " ";
				}
				fout << endl;
			}
		}
		else if (type == -1) {
			if (p->line[condition]<= add_value) {
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						fout << p->line[j] << " ";
				}
				fout << endl;
			}
		}
		else if (type == 1) {
			if (p->line[condition] >= add_value) {
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						fout << p->line[j] << " ";
				}
				fout << endl;
			}
		}
		else if (type == -2) {
			if (p->line[condition] < add_value) {
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						fout << p->line[j] << " ";
				}
				fout << endl;
			}
		}
		else if (type == 2) {
			if (p->line[condition] > add_value) {
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						fout << p->line[j] << " ";
				}
				fout << endl;
			}
		}
		else if (type == 3) {
			if (p->line[condition] != add_value) {
				for (size_t j = 0; j < col_num; j++) {
					if (index[j])
						fout << p->line[j] << " ";
				}
				fout << endl;
			}
		}
	}
	fout.close();
	fout.clear();
	return;
}

void Tableop::showTable_all_limited(Table *h, string add_limit, string add_value, int type) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();

	size_t width[30];
	int i = 0;
	for (int j = 0; j < 30; j++)
		width[j] = 0;

	for (Table *p = h; p != NULL; p = p->next) {
		i = 0;
		for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
			width[i] = width[i] >(*iter).length() ? width[i] : (*iter).length();
			i++;
		}
	}
	int condition = -1;
	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == add_limit) {
			condition = i;
			break;
		}
	}

	int id = 0;
	cout << setw(6) << setiosflags(ios::left) << "ID";
	id++;
	for (size_t j = 0; j < col_num; j++) {
		cout << setw(width[j] + 1) << setiosflags(ios::left) << titles[j];
	}
	cout << endl;
	for (Table *p = h->next; p != NULL; p = p->next) {
		i = 0;
		if (type == 0) {
			if (p->line[condition] == add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
					i++;
				}
				cout << endl;
				id++;
			}
		}
		else if (type == -1) {
			if (p->line[condition] <= add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
					i++;
				}
				cout << endl;
				id++;
			}
		}
		else if (type == 1) {
			if (p->line[condition] >= add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
					i++;
				}
				cout << endl;
				id++;
			}
		}
		else if (type == -2) {
			if (p->line[condition] < add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
					i++;
				}
				cout << endl;
				id++;
			}
		}
		else if (type == 2) {
			if (p->line[condition] > add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
					i++;
				}
				cout << endl;
				id++;
			}
		}
		else if (type == 3) {
			if (p->line[condition] != add_value) {
				cout << setw(6) << setiosflags(ios::left) << id;
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					cout << setw(width[i] + 1) << setiosflags(ios::left) << (*iter);
					i++;
				}
				cout << endl;
				id++;
			}
		}
	}
}

void Tableop::showTable_all_limited(Table *h, string add_limit, string add_value, int type, char *filename) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();

	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}
	int i = 0;
	int condition = -1;
	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == add_limit) {
			condition = i;
			break;
		}
	}

	
	for (size_t j = 0; j < col_num; j++) {
		fout<<titles[j]<<" ";
	}
	fout << endl;
	for (Table *p = h->next; p != NULL; p = p->next) {
		i = 0;
		if (type == 0) {
			if (p->line[condition] == add_value) {
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					fout << (*iter) << " ";
					i++;
				}
				fout << endl;
			}
		}
		else if (type == -1) {
			if (p->line[condition]<= add_value) {
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					fout << (*iter) << " ";
					i++;
				}
				fout << endl;
			}
		}
		else if (type == 1) {
			if (p->line[condition] >= add_value) {
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					fout << (*iter) << " ";
					i++;
				}
				fout << endl;
			}
		}
		else if (type == -2) {
			if (p->line[condition] < add_value) {
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					fout << (*iter) << " ";
					i++;
				}
				fout << endl;
			}
		}
		else if (type == 2) {
			if (p->line[condition] > add_value) {
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					fout << (*iter) << " ";
					i++;
				}
				fout << endl;
			}
		}
		else if (type == 3) {
			if (p->line[condition] != add_value) {
				for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
					fout << (*iter) << " ";
					i++;
				}
				fout << endl;
			}
		}
	}
	fout.close();
	fout.clear();
	return;
}

void Tableop::showTable_maxminave(Table *h, string condition, int type) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();
	
	int conindex = -1;
	int i = 0;

	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == condition) {
			conindex = i;
			break;
		}
	}
	
	size_t width[30];
	for (int j = 0; j < 30; j++)
		width[j] = 0;

	for (Table *p = h; p != NULL; p = p->next) {
		i = 0;
		for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++) {
			width[i] = width[i] >(*iter).length() ? width[i] : (*iter).length();
			i++;
		}
	}
	
	if (type == 1) {
		Table *q = new Table;
		q = h->next;
		vector<string>max(q->line);
		while (q!= NULL) {
			if (q->line[conindex] > max[conindex]&&q->line[conindex] != "\t")
				max.assign(q->line.begin(),q->line.end());
			q = q->next;
		}
		Table *r=new Table;
		r->line.assign(max.begin(),max.end()); 
		r->next=NULL;
		for(Table *w=h->next;w!=NULL;w=w->next) {
			if(w->line[conindex]==max[conindex]) {
				bool isdifferent=false;
				for(size_t u=0;u<col_num;u++) {
					if(w->line[u]!=max[u]) {
						isdifferent=true;
						break;
					}
				}
				if(isdifferent) {
					Table *n=new Table;
					n->line.assign(w->line.begin(),w->line.end());
					n->next=NULL;
					Table *t=r;
					while(t->next!=NULL)
						t=t->next;
					t->next=n;
				}
			}
		}
		cout << setw(6) << setiosflags(ios::left) << "ID";
		for(size_t j=0;j<col_num;j++){
			if(j+1!=col_num)
				cout << setw(width[j]+1)<< setiosflags(ios::left)<<titles[j];
			else
				cout << setw(width[j]+1)<< setiosflags(ios::left)<<titles[j]<<endl;
		}
		int id=1;
		for(Table *w=r;w!=NULL;w=w->next) {
			cout<<setw(6)<< setiosflags(ios::left) << id;
			for(size_t j=0;j<col_num;j++){
				if(j+1!=col_num)
					cout << setw(width[j]+1)<< setiosflags(ios::left)<<w->line[j];
				else
					cout << setw(width[j]+1)<< setiosflags(ios::left)<<w->line[j]<<endl;
			}
			id++;
		}
		return;
	}

	else if (type == 2) {
		Table *q = new Table;
		q = h->next;
		vector<string>min(q->line);
		while (q != NULL) {
			if (q->line[conindex] < min[conindex]&&q->line[conindex] != "\t")
				min.assign(q->line.begin(),q->line.end());
			q = q->next;
		}
		Table *r=new Table;
		r->line.assign(min.begin(),min.end()); 
		r->next=NULL;
		for(Table *w=h->next;w!=NULL;w=w->next) {
			if(w->line[conindex]==min[conindex]) {
				bool isdifferent=false;
				for(size_t u=0;u<col_num;u++) {
					if(w->line[u]!=min[u]) {
						isdifferent=true;
						break;
					}
				}
				if(isdifferent) {
					Table *n=new Table;
					n->line.assign(w->line.begin(),w->line.end());
					n->next=NULL;
					Table *t=r;
					while(t->next!=NULL)
						t=t->next;
					t->next=n;
				}
			}
		}
		cout << setw(6) << setiosflags(ios::left) << "ID";
		for(size_t j=0;j<col_num;j++){
			if(j+1!=col_num)
				cout << setw(width[j]+1)<< setiosflags(ios::left)<<titles[j];
			else
				cout << setw(width[j]+1)<< setiosflags(ios::left)<<titles[j]<<endl;
		}
		int id=1;
		for(Table *w=r;w!=NULL;w=w->next) {
			cout<<setw(6)<< setiosflags(ios::left) << id;
			for(size_t j=0;j<col_num;j++){
				if(j+1!=col_num)
					cout << setw(width[j]+1)<< setiosflags(ios::left)<<w->line[j];
				else
					cout << setw(width[j]+1)<< setiosflags(ios::left)<<w->line[j]<<endl;
			}
			id++;
		}
		return;
	}

	else if (type == 3) {
		Table *q = new Table;
		q = h->next;
		double sum =0;
		int num = 0;
		while (q != NULL) {
			if (q->line[conindex] != "\t") {
				sum += stod(q->line[conindex]);
				num++;
			}
			q = q->next;
		}
		cout << setw(6) << setiosflags(ios::left) << "ID";
		cout << titles[conindex];
		cout << endl;
		cout << setw(6) << setiosflags(ios::left) << "1";
		cout << (double)sum/num<<endl;
		return;
	}
}

void Tableop::showTable_maxminave(Table *h, string condition, int type, char *filename) {
	if (h->next == NULL)
		return;
	vector<string> titles(h->line);
	size_t col_num = titles.size();


	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	int conindex = -1;
	int i = 0;

	for (i = 0; i<(int)col_num; i++) {
		if (titles[i] == condition) {
			conindex = i;
			break;
		}
	}

	if (type == 1) {
		Table *q = new Table;
		q = h->next;
		vector<string>max(q->line);
		while (q != NULL) {
			if (q->line[conindex] > max[conindex]&&q->line[conindex] != "\t")
				max.assign(q->line.begin(),q->line.end());
			q = q->next;
		}
		Table *r=new Table;
		r->line.assign(max.begin(),max.end()); 
		r->next=NULL;
		for(Table *w=h->next;w!=NULL;w=w->next) {
			if(w->line[conindex]==max[conindex]) {
				bool isdifferent=false;
				for(size_t u=0;u<col_num;u++) {
					if(w->line[u]!=max[u]) {
						isdifferent=true;
						break;
					}
				}
				if(isdifferent) {
					Table *n=new Table;
					n->line.assign(w->line.begin(),w->line.end());
					n->next=NULL;
					Table *t=r;
					while(t->next!=NULL)
						t=t->next;
					t->next=n;
				}
			}
		}
		for(size_t j=0;j<col_num;j++){
			if(j+1!=col_num)
				fout << titles[j]<<" ";
			else
				fout << titles[j]<<endl;
		}
		for(Table *w=r;w!=NULL;w=w->next) {
			for(size_t j=0;j<col_num;j++){
				if(j+1!=col_num)
					fout<<w->line[j]<<" ";
				else
					fout<<w->line[j]<<endl;
			}
		}
		return;
	}

	else if (type == 2) {
		Table *q = new Table;
		q = h->next;
		vector<string>min(q->line);
		while (q != NULL) {
			if (q->line[conindex] < min[conindex]&&q->line[conindex] != "\t")
				min.assign(q->line.begin(),q->line.end());
			q = q->next;
		}
		Table *r=new Table;
		r->line.assign(min.begin(),min.end()); 
		r->next=NULL;
		for(Table *w=h->next;w!=NULL;w=w->next) {
			if(w->line[conindex]==min[conindex]) {
				bool isdifferent=false;
				for(size_t u=0;u<col_num;u++) {
					if(w->line[u]!=min[u]) {
						isdifferent=true;
						break;
					}
				}
				if(isdifferent) {
					Table *n=new Table;
					n->line.assign(w->line.begin(),w->line.end());
					n->next=NULL;
					Table *t=r;
					while(t->next!=NULL)
						t=t->next;
					t->next=n;
				}
			}
		}
		for(size_t j=0;j<col_num;j++){
			if(j+1!=col_num)
				fout << titles[j]<<" ";
			else
				fout << titles[j]<<endl;
		}
		for(Table *w=r;w!=NULL;w=w->next) {
			for(size_t j=0;j<col_num;j++){
				if(j+1!=col_num)
					fout<<w->line[j]<<" ";
				else
					fout<<w->line[j]<<endl;
			}
		}
		return;
	}

	else if (type == 3) {
		Table *q = new Table;
		q = h->next;
		double sum = 0;
		int num = 0;
		while (q != NULL) {
			if (q->line[conindex] != "\t") {
				sum += stod(q->line[conindex]);
				num++;
			}
			q = q->next;
		}
		fout << titles[conindex];
		fout << endl;
		fout << (double)sum / num << endl;
		return;
	}
}
