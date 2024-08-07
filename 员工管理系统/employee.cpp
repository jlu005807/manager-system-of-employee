#define _CRT_SECURE_NO_WARNINGS
#include"employee.h"

inline void showtime(time_t time) {
	struct tm* p;
	p = localtime(&time);
	printf("%04d.%02d.%02d  %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

employee::employee(int id, string name, int deptid, time_t nowtime)
{
	this->_id = id;
	this->_name = name;
	this->_deptid = deptid;
	this->mod_time = nowtime;
}

void employee::showinfo()
{
	cout << "职工编号：" << this->_id << endl;
	cout << "职工姓名：" << this->_name << endl;
	cout << "职工岗位：" << this->_deptid << endl;
	cout << "岗位职责：完成任务" << endl;
	cout << "最后修改时间：";
	showtime(mod_time);
}

string employee::getdeptname() {

	return string("普通员工");
}