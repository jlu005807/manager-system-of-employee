#pragma once
#include<iostream>
#include<string>
#include"worker.h"
#include<ctime>

using namespace std;

class manager :public worker {
public:
	manager(int id, string name, int deptid, time_t nowtime);
	virtual void showinfo();
	virtual string getdeptname();
};
