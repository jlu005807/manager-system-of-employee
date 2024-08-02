#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"worker.h"
#include<ctime>

class employee :public worker {
public:
	employee(int id, string name, int deptid,  time_t nowtime);
	virtual void showinfo();
	virtual string getdeptname();

};
