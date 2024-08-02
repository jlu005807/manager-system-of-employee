#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<ctime>

class worker
{
public:
	virtual void showinfo() = 0;
	virtual string getdeptname() = 0;
	int _id;
	int _deptid;
	string _name;
	time_t mod_time;
};
