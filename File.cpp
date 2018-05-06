#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Data.h"
#include "File.h"

void File::readTable(Table *&h,char *filename) {
	std::ifstream fin(filename, std::ios::in);
	if (!fin) {
		cout << "File open error!\n";
		return;
	}

	char buf[1024] = { '\0' };
	while (fin.getline(buf, sizeof(buf),'\n')) {
		std::stringstream words(buf);
		string cell;
		Table *tmp = new Table;
		tmp->next = NULL;
		while (getline(words, cell,' ')) {
			tmp->line.push_back(cell);
		}

		if (h == NULL) {
			h = tmp;
		}

		else {
			Table *p = h;
			while(p->next!=NULL)
				p = p->next;
			p->next = tmp;
		}
	}

	fin.clear();
	fin.close();
	return;
}

void File::writeTable(Table *h,char *filename) {
	if (h == NULL) {
		cout << "Not valid table!\n";
		return;
	}

	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
	ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	for (Table *p = h; p != NULL; p = p->next) {
		for (vector<string>::iterator iter = p->line.begin(); iter != p->line.end(); iter++)
			fout << (*iter)<<" ";
		fout << endl;
	}
	fout.close();
	fout.clear();
	return;
}

void File::readRecord(Record *&h) {
	string filename = "Record.txt";
	ifstream fin(filename, std::ios::in);
	if (!fin) {
		cout << "File open error!\n";
		return;
	}

	char buf[1024] = { '\0' };
	while (fin.getline(buf, sizeof(buf),'\n')) {
		std::stringstream words(buf);
		string cell;
		Record *tmp = new Record;
		tmp->next = NULL;
		while (getline(words,cell,' ')) {
			tmp->tablename=cell;
			getline(words, cell, ' ');
			tmp->filename=cell;
		}

		if (h == NULL)
			h = tmp;
		else {
			Record *p = h;
			while (p->next != NULL)
				p = p->next;
			p->next = tmp;
		}
	}

	fin.clear();
	fin.close();
	return;
}

void File::writeRecord(Record *h) {
	if (h == NULL) {
		cout << "Not valid table!\n";
		return;
	}

	string filename = "Record.txt";
	FILE* fp;
	fp = fopen(filename.c_str(), "w");
	fclose(fp);
	std::ofstream fout(filename);
	if (!fout) {
		cout << "File open error!\n";
		return;
	}

	for (Record *p = h; p != NULL; p = p->next) {
		fout <<p->tablename<<" "<<p->filename<< endl;
	}
	fout.close();
	fout.clear();
	return;
}