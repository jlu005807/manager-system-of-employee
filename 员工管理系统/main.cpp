#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"workermanager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;

int main()
{
	workermanager wm;
	int choice;
	while (1) {
		wm.showmenu();
		cout << "请选择功能：";
		cin >> choice;
		while (choice < 0 || choice>7 || cin.fail())
		{
			cin.ignore();
			cin.clear();
			while (char c = getchar() != '\n');
			cout << "输入有误，请重新输入：";
			cin >> choice;
		}
		switch (choice)
		{
		case 0: {
			wm.exitsystem();
			break;
		}
		case 1: {
			wm.addemp();
			break;
		}
		case 2: {
			wm.show_emp();
			break;
		}
		case 3: {
			wm.del_emp();
			break;
		}
		case 4: {
			wm.mod_emp();
			break;
		}
		case 5: {
			wm.find_emp();
			break;
		}
		case 6: {
			wm.sort_emp();
			break;
		}
		case 7: {
			wm.clean_file();
			break;
		}
		default: {
			cout << "输入有误，请重新输入" << endl;
			system("cls");
			break;
		}
	  }
	}
	system("pause");
	return 0;
}