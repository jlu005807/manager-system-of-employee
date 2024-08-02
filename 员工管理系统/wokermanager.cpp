
#include"workermanager.h"


bool Isalldigit(string str) {
	for (int i = 0; i < sizeof(str); i++) {
		if (!isdigit(str[i]))return false;
	}
	return true;
}



void m_clean() {
	char cl;
	cl = getchar();
	while ((cl = getchar()) != '\n');
	cin.clear();

}
int ischioce(string str) {
	if (sizeof(str) != 1)return -1;
	else if (Isalldigit(str)) {
		return (int)str[0] - 48;
	}
	else {
		return -1;
	}
}


workermanager::workermanager()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		this->_empnum = 0;
		this->_emparray = NULL;
		this->_fileisempty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->_empnum = 0;
		this->_emparray = NULL;
		this->_fileisempty = true;
		ifs.close();
	}
	int num =this->get_empnum();
	this->_empnum = num;
	this->_emparray = new worker * [this->_empnum];
	this->init_emp();//初始化

}

void workermanager::showmenu()
{
	cout << "******************************************" << endl;
	cout << "*************  职工管理系统  *************" << endl;
	cout << "************  0-退出管理系统  ************" << endl;
	cout << "************  1-增加职工信息  ************" << endl;
	cout << "************  2-显示职工信息  ************" << endl;
	cout << "************  3-删除职工信息  ************" << endl;
	cout << "************  4-修改职工信息  ************" << endl;
	cout << "************  5-查找职工信息  ************" << endl;
	cout << "************  6-按照编号排序  ************" << endl;
	cout << "************  7-清空所有文档  ************" << endl;
	cout << "******************************************" << endl;
}

void workermanager::exitsystem() {
	cout << "确定退出系统?" << endl;
	cout << "  0--确定" << endl;
	cout << "  1--返回" << endl;
	cout << "请输入你的选择：";
	string choice;
	cin >> choice;
	while (!regex_match(choice,regex("(0|1)$")))
	{
		cin.ignore();
		cout << "输入有误，请重新输入：";
		while (char c = getchar() != '\n');
		cin.clear();
		cin >> choice;
	}
	if (choice == "0") {
		cout << "  退出成功" << endl;
		cout << "欢迎下次使用" << endl;
		system("pause");
		exit(0);
	}
	else {
		cout << "返回成功" << endl;
		system("pause");
		system("cls");
		return;
	}
}

void workermanager::addemp()
{
	cout << "请输入添加职工的数量：";
	int add_num;
	cin >> add_num;
	while (add_num <= 0||cin.fail() ) {
		cin.ignore();
		cout << "输入错误，请重新输入：";
		m_clean();
		cin >> add_num;
	}
	int new_size = this->_empnum + add_num;
	worker** new_space = new worker * [new_size];
	if (this->_emparray != NULL) {
		for (int i = 0; i < this->_empnum; i++) {
			new_space[i] = this->_emparray[i];
		}
	}
	for (int i = 0; i < add_num; i++) {
		int id=-1;
		string name;
		int deptid;

		cout << "请输入第" << i + 1 << "个新职工的编号：" ;
		cin >> id;
		while (id <= 0||cin.fail()||isexist(id)!=-1) {
			cin.ignore();
			if (isexist(id) == -1) {
				cout << "输入错误，请重新输入：";
				m_clean();
			}
			else cout << "此编号已存在！请重新输入：";
			cin >> id;
		}
		
		cout << "请输入第" << i + 1 << "个新职工的姓名：";
		cin >> name;
		cout << "请输入第" << i + 1 << "个新职工的岗位" << endl;
		cout << "1--普通职工" << endl;
		cout << "2--经理" << endl;
		cout << "3--总裁" << endl;
		cin >> deptid;
		while (deptid < 0 || deptid > 3||cin.fail() ) {
			cin.ignore();
			cout << "输入错误，请重新输入：";
			if(cin.fail())m_clean();
			cin >> deptid;
		}
		worker* _worker = NULL;
		time_t nowtime = time(0);
		switch (deptid)
		{
		case 1:_worker = new employee(id, name, 1, nowtime); break;
		case 2:_worker = new manager(id, name, 2, nowtime); break;
		case 3:_worker = new boss(id, name, 3, nowtime); break;
		}
		new_space[this->_empnum + i] = _worker;
	}
	delete[] this->_emparray;

	this->_emparray = new_space;

	this->_empnum = new_size;

	this->_fileisempty = false;

	cout << "成功添加" << endl;
	this->savefile();
	system("pause");
	system("cls");
}
void workermanager::savefile()
{
	ofstream ofs;
	ofs.open(filename, ios::out);//以输出方式打开文件--写文件
	for (int i = 0; i < this->_empnum; i++)
	{
		ofs << this->_emparray[i]->_id << " "
			<< this->_emparray[i]->_name << " "
			<< this->_emparray[i]->_deptid << endl;
	}
	ofs.close();
}

int workermanager::get_empnum()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	int id;
	string name;
	int d_id;
	int num = 0;//计数器
	while (ifs >> id && ifs >> name && ifs >> d_id) {
		num++;
	}
	return num;
}

void workermanager::init_emp()
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	int id;
	string name;
	int d_id;
	int num = 0;
	int index=0;
	while (ifs >> id && ifs >> name && ifs >> d_id)
	{
		worker* work = NULL;
		switch (d_id)
		{
		case 1:work = new employee(id, name, 1, time(0));
		case 2:work = new manager(id, name, 2, time(0));
		case 3:work = new boss(id, name, 2, time(0));
		}
		this->_emparray[index++] = work;
	}
	ifs.close();
}

void workermanager::show_emp()
{
	if (this->_fileisempty)
	{
		cout << "文件不存在或记录为空" << endl;

	}
	else
	{
		for (int i = 0; i < _empnum; i++) {
			this->_emparray[i]->showinfo();
			cout << endl<< "**********************************" << endl;
		}
	}
	cout << endl;
	system("pause");
	system("cls");
}

void workermanager::del_emp()
{
	if (this->_fileisempty)
	{
		cout << "文件不存在或记录为空" << endl;

	}
	else
	{
		cout << "请输入你要删除的职工的编号：";
		int id;
		cin >> id;
		while (id<=0||cin.fail()) {
			cin.ignore();
			cout << "输入有误，请重新输入：";
			m_clean();
			cin >> id;
		}
		int index = this->isexist(id);
		if (index != -1)
		{
			cout << "确定删除该职工?" << endl;
			cout << "  0--确定" << endl;
			cout << "  1--返回" << endl;
			int choice;
			cin >> choice;
			while ( choice < 0 || choice>1||cin.fail() )
			{
				cin.ignore();
				cout << "输入有误，请重新输入：";
				m_clean();
				cin >> choice;
			}
			if (choice == 0) {
				for (int i = 0; i < this->_empnum - 1; i++)
				{
					this->_emparray[i] = this->_emparray[i + 1];
				}
				this->_empnum--;
				this->savefile();
				cout << "删除成功" << endl;
			}
			else
			{
				cout << "返回成功" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workermanager::mod_emp()
{
	if (this->_fileisempty)
	{
		cout << "文件不存在或记录为空" << endl;

	}
	else
	{
		cout << "请输入修改职工的编号：";
		int id;
		cin >> id;
		while (cin.fail())
		{
			cin.ignore();
			cout << "输入有误，请重新输入：";
			m_clean();
			cin >> id;

		}
		int ret = this->isexist(id);
		if (ret != -1) {
			cout << "查找到" << id << "号职工" << endl;
			this->_emparray[ret]->showinfo();
			cout << "***************************" << endl;
			cout << "请输入要修改的内容：" ;
			cout << "1-编号" << endl;
			cout << "2-姓名" << endl;
			cout << "3-岗位" << endl;
			cout << "4-重新编写" << endl;
			cout << "0-返回" << endl;
			int  select;
			cin >> select;
			while ( select < 0 || select>4 ||cin.fail())
			{
				cin.ignore();
				cout << "输入有误，请重新输入：";
				m_clean();
				cin >> select;
			}
			if (select== 0) {
				cout << "返回成功" << endl;
				system("pause");
				system("cls");
				return;
			}
			else if (select == 1) {
				int newid;
				cout << "请输入新的编号：";
				cin >> newid;
				while (newid<=0||cin.fail()) {
					cin.ignore();
					cout << "输入错误，请重新输入：";
					m_clean();
					cin >> newid;

				}
				this->_emparray[ret]->mod_time = time(0);
				this->_emparray[ret]->_id = newid;
			}
			else if(select == 2){
				string newname;
				cout << "请输入新的姓名：";
				cin >> newname;
				this->_emparray[ret]->mod_time = time(0);
				this->_emparray[ret]->_name = newname;
			}
			else if (select == 3) {
				int deptid;
				cout << "请输入新岗位" << endl;
				cout << "1--普通职工" << endl;
				cout << "2--经理" << endl;
				cout << "3--总裁" << endl;
				cin >> deptid;
				while (cin.fail() || deptid < 0 || deptid > 4) {
					cin.ignore();
					cout << "输入错误，请重新输入：";
					m_clean();
					cin >> deptid;
				}
				this->_emparray[ret]->_deptid = deptid;
				this->_emparray[ret]->mod_time = time(0);
			}
			else if (select == 4) {
				delete this->_emparray[ret];

				int newid;
				string newname;
				
				cout << "请输入新的编号：";
				cin >> newid;
				while (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "输入错误，请重新输入：";
					cin >> newid;

				}
				cout << "请输入新的姓名：";
				
				cin >> newname;

				int deptid;
				cout << "请输入新岗位" << endl;
				cout << "1--普通职工" << endl;
				cout << "2--经理" << endl;
				cout << "3--总裁" << endl;
				
				cin >> deptid;
				while (cin.fail() || deptid < 0 || deptid > 4) {
					cin.ignore();
					cout << "输入错误，请重新输入：" ;
					m_clean();
					cin >> deptid;
				}

				worker* work = NULL;
				switch (deptid)
				{
				case 1:work = new employee(newid, newname, deptid, time(0)); break;
				case 2:work = new manager(newid, newname, deptid, time(0)); break;
				case 3:work = new boss(newid, newname, deptid, time(0)); break;
				}
				this->_emparray[ret] = work;
				cout << "修改成功" << endl;
				this->savefile();
			}
				
		}
        else {
			cout << "修改失败，未找到该职工" << endl;
		}

	}
	system("pause");
	system("cls");
}


void workermanager::find_emp()
{
	if (this->_fileisempty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1-按照职工编号查找" << endl;
		cout << "2-按照职工姓名查找" << endl;

		int select;
		cin >> select;
		while (cin.fail()) {
			cin.ignore();
			cout << "输入有误，请重新输入：";
			m_clean();
			cin >> select;
		}
		if (select == 1) {
			int id;
			cout << "请输入您要查找的职工的编号：";
			cin >> id;
			while (cin.fail()) {
				cin.ignore();
				cout << "输入有误，请重新输入：";
				m_clean();
				cin >> id;
			}
			int ret = isexist(id);
			if (ret != -1) {
				cout << "查找成功，该职工信息如下：" << endl;
				this->_emparray[ret]->showinfo();
			}
			else {
				cout << "查找失败，未找到该职工" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入您要查找的职工的姓名：";
			cin >> name;
			bool flag = true;
			for (int i = 0; i < _empnum && flag; i++)
			{
				if (this->_emparray[i]->_name == name)
				{
					cout << "查找成功，该职工信息如下：" << endl;
					this->_emparray[i]->showinfo();
					cout << endl;
					flag = false;
				}
			}
			if (flag == true)
			{
				cout << "查找失败，未找到该职工" << endl;
			}
		}
		system("pause");
		system("cls");
	}
}

int workermanager::isexist(int id)
{
	int index = -1;
	for (int i = 0; i < this->_empnum; i++)
	{
		if (this->_emparray[i]->_id == id) {
			index = i;
			break;
		}
	}
	return index;
}

void workermanager::sort_emp()
{
	if (this->_fileisempty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1-按照职工编号进行升序" << endl;
		cout << "2-按照职工编号进行降序" << endl;
		cout << "请输入你的选择：";
		int select;
		cin >> select;
		while (cin.fail()||select>2||select<1) {
			cin.ignore();
			cout << "输入有误，请重新输入：";
			m_clean();
			cin >> select;
		}
		for (int i = 0; i < this->_empnum; i++)
		{
			int minormax = i;
			for (int j = i + 1; j < this->_empnum; j++)
			{
				if (select == 1)
				{
					if (this->_emparray[minormax]->_id > this->_emparray[j]->_id) {
						minormax = j;
					}
				}
				else {
					if (this->_emparray[minormax]->_id < this->_emparray[j]->_id) {
						minormax = j;
					}
				}
			}
			if (i != minormax)
			{
				worker* temp = this->_emparray[i];
				this->_emparray[i] = this->_emparray[minormax];
				this->_emparray[minormax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->savefile();
		this->show_emp();

	}
}

void workermanager::clean_file()
{
	if (this->_fileisempty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "确定清空吗？" << endl;
		cout << "  0-确定" << endl;
		cout << "  1-取消" << endl;
		cout << "请输入你的选择：";
		int select;
		cin >> select;
		while (cin.fail() || select < 0 || select>1)
		{
			cin.ignore();
			cout << "输入有误，请重新输入：";
			m_clean();
			cin >> select;
		}
		if (select == 0) {
			ofstream ofs;
			ofs.open(filename, ios::trunc);
			ofs.close();
			if (this->_emparray != NULL) {
				for (int i = 0; i < this->_empnum; i++) {
					delete this->_emparray[i];
				}
				delete this->_emparray;
				this->_emparray = NULL;
				this->_empnum = 0;
				this->_fileisempty = true;
			}
			cout << "清空成功" << endl;
			system("pause");
			system("cls");
		}
		else {
			cout << "取消成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

workermanager::~workermanager()
{
	if (this->_emparray != NULL)
	{
		for (int i = 0; i < this->_empnum; i++)
		{
			delete this->_emparray[i];
		}
		delete this->_emparray;
		this->_emparray = NULL;

	}
}