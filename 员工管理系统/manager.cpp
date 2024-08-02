#define _CRT_SECURE_NO_WARNINGS
#include"manager.h"

inline void showtime(time_t time) {
	struct tm* p;
	p = localtime(&time);
	printf("%04d.%02d.%02d  %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

manager::manager(int id, string name, int deptid, time_t nowtime)
{
	this->_id = id;
	this->_name = name;
	this->_deptid = deptid;
	this->mod_time = nowtime;
}

void manager::showinfo()
{
	cout << "ְ����ţ�" << this->_id << endl;
	cout << "ְ��������" << this->_name << endl;
	cout << "ְ����λ��" << this->_deptid << endl;
	cout << "��λְ������ܲõ������·��������ͨԱ��" << endl;
	cout << "����޸�ʱ�䣺";
	showtime(mod_time);
}

string manager::getdeptname() {

	return string("����");
}