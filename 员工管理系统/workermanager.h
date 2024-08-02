#pragma once
#include<iostream>
#include<string>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#include<ctime>
#include<regex>
#define filename "test.txt"

using namespace std;

class workermanager
{
public:
	workermanager();
	void showmenu();
	void exitsystem();
	int _empnum;
	worker** _emparray;
	void addemp();
	void savefile();
	bool _fileisempty;
	int get_empnum();
	void init_emp();
	void  show_emp();
	int isexist(int id);
	void del_emp();
	void mod_emp();
	void find_emp();
	void sort_emp();
	void clean_file();

	~workermanager();
};