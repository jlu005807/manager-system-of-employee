
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
	this->init_emp();//��ʼ��

}

void workermanager::showmenu()
{
	cout << "******************************************" << endl;
	cout << "*************  ְ������ϵͳ  *************" << endl;
	cout << "************  0-�˳�����ϵͳ  ************" << endl;
	cout << "************  1-����ְ����Ϣ  ************" << endl;
	cout << "************  2-��ʾְ����Ϣ  ************" << endl;
	cout << "************  3-ɾ��ְ����Ϣ  ************" << endl;
	cout << "************  4-�޸�ְ����Ϣ  ************" << endl;
	cout << "************  5-����ְ����Ϣ  ************" << endl;
	cout << "************  6-���ձ������  ************" << endl;
	cout << "************  7-��������ĵ�  ************" << endl;
	cout << "******************************************" << endl;
}

void workermanager::exitsystem() {
	cout << "ȷ���˳�ϵͳ?" << endl;
	cout << "  0--ȷ��" << endl;
	cout << "  1--����" << endl;
	cout << "���������ѡ��";
	string choice;
	cin >> choice;
	while (!regex_match(choice,regex("(0|1)$")))
	{
		cin.ignore();
		cout << "�����������������룺";
		while (char c = getchar() != '\n');
		cin.clear();
		cin >> choice;
	}
	if (choice == "0") {
		cout << "  �˳��ɹ�" << endl;
		cout << "��ӭ�´�ʹ��" << endl;
		system("pause");
		exit(0);
	}
	else {
		cout << "���سɹ�" << endl;
		system("pause");
		system("cls");
		return;
	}
}

void workermanager::addemp()
{
	cout << "���������ְ����������";
	int add_num;
	cin >> add_num;
	while (add_num <= 0||cin.fail() ) {
		cin.ignore();
		cout << "����������������룺";
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

		cout << "�������" << i + 1 << "����ְ���ı�ţ�" ;
		cin >> id;
		while (id <= 0||cin.fail()||isexist(id)!=-1) {
			cin.ignore();
			if (isexist(id) == -1) {
				cout << "����������������룺";
				m_clean();
			}
			else cout << "�˱���Ѵ��ڣ����������룺";
			cin >> id;
		}
		
		cout << "�������" << i + 1 << "����ְ����������";
		cin >> name;
		cout << "�������" << i + 1 << "����ְ���ĸ�λ" << endl;
		cout << "1--��ְͨ��" << endl;
		cout << "2--����" << endl;
		cout << "3--�ܲ�" << endl;
		cin >> deptid;
		while (deptid < 0 || deptid > 3||cin.fail() ) {
			cin.ignore();
			cout << "����������������룺";
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

	cout << "�ɹ����" << endl;
	this->savefile();
	system("pause");
	system("cls");
}
void workermanager::savefile()
{
	ofstream ofs;
	ofs.open(filename, ios::out);//�������ʽ���ļ�--д�ļ�
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
	int num = 0;//������
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;

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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;

	}
	else
	{
		cout << "��������Ҫɾ����ְ���ı�ţ�";
		int id;
		cin >> id;
		while (id<=0||cin.fail()) {
			cin.ignore();
			cout << "�����������������룺";
			m_clean();
			cin >> id;
		}
		int index = this->isexist(id);
		if (index != -1)
		{
			cout << "ȷ��ɾ����ְ��?" << endl;
			cout << "  0--ȷ��" << endl;
			cout << "  1--����" << endl;
			int choice;
			cin >> choice;
			while ( choice < 0 || choice>1||cin.fail() )
			{
				cin.ignore();
				cout << "�����������������룺";
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
				cout << "ɾ���ɹ�" << endl;
			}
			else
			{
				cout << "���سɹ�" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workermanager::mod_emp()
{
	if (this->_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;

	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�";
		int id;
		cin >> id;
		while (cin.fail())
		{
			cin.ignore();
			cout << "�����������������룺";
			m_clean();
			cin >> id;

		}
		int ret = this->isexist(id);
		if (ret != -1) {
			cout << "���ҵ�" << id << "��ְ��" << endl;
			this->_emparray[ret]->showinfo();
			cout << "***************************" << endl;
			cout << "������Ҫ�޸ĵ����ݣ�" ;
			cout << "1-���" << endl;
			cout << "2-����" << endl;
			cout << "3-��λ" << endl;
			cout << "4-���±�д" << endl;
			cout << "0-����" << endl;
			int  select;
			cin >> select;
			while ( select < 0 || select>4 ||cin.fail())
			{
				cin.ignore();
				cout << "�����������������룺";
				m_clean();
				cin >> select;
			}
			if (select== 0) {
				cout << "���سɹ�" << endl;
				system("pause");
				system("cls");
				return;
			}
			else if (select == 1) {
				int newid;
				cout << "�������µı�ţ�";
				cin >> newid;
				while (newid<=0||cin.fail()) {
					cin.ignore();
					cout << "����������������룺";
					m_clean();
					cin >> newid;

				}
				this->_emparray[ret]->mod_time = time(0);
				this->_emparray[ret]->_id = newid;
			}
			else if(select == 2){
				string newname;
				cout << "�������µ�������";
				cin >> newname;
				this->_emparray[ret]->mod_time = time(0);
				this->_emparray[ret]->_name = newname;
			}
			else if (select == 3) {
				int deptid;
				cout << "�������¸�λ" << endl;
				cout << "1--��ְͨ��" << endl;
				cout << "2--����" << endl;
				cout << "3--�ܲ�" << endl;
				cin >> deptid;
				while (cin.fail() || deptid < 0 || deptid > 4) {
					cin.ignore();
					cout << "����������������룺";
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
				
				cout << "�������µı�ţ�";
				cin >> newid;
				while (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "����������������룺";
					cin >> newid;

				}
				cout << "�������µ�������";
				
				cin >> newname;

				int deptid;
				cout << "�������¸�λ" << endl;
				cout << "1--��ְͨ��" << endl;
				cout << "2--����" << endl;
				cout << "3--�ܲ�" << endl;
				
				cin >> deptid;
				while (cin.fail() || deptid < 0 || deptid > 4) {
					cin.ignore();
					cout << "����������������룺" ;
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
				cout << "�޸ĳɹ�" << endl;
				this->savefile();
			}
				
		}
        else {
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}

	}
	system("pause");
	system("cls");
}


void workermanager::find_emp()
{
	if (this->_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1-����ְ����Ų���" << endl;
		cout << "2-����ְ����������" << endl;

		int select;
		cin >> select;
		while (cin.fail()) {
			cin.ignore();
			cout << "�����������������룺";
			m_clean();
			cin >> select;
		}
		if (select == 1) {
			int id;
			cout << "��������Ҫ���ҵ�ְ���ı�ţ�";
			cin >> id;
			while (cin.fail()) {
				cin.ignore();
				cout << "�����������������룺";
				m_clean();
				cin >> id;
			}
			int ret = isexist(id);
			if (ret != -1) {
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->_emparray[ret]->showinfo();
			}
			else {
				cout << "����ʧ�ܣ�δ�ҵ���ְ��" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������Ҫ���ҵ�ְ����������";
			cin >> name;
			bool flag = true;
			for (int i = 0; i < _empnum && flag; i++)
			{
				if (this->_emparray[i]->_name == name)
				{
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
					this->_emparray[i]->showinfo();
					cout << endl;
					flag = false;
				}
			}
			if (flag == true)
			{
				cout << "����ʧ�ܣ�δ�ҵ���ְ��" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1-����ְ����Ž�������" << endl;
		cout << "2-����ְ����Ž��н���" << endl;
		cout << "���������ѡ��";
		int select;
		cin >> select;
		while (cin.fail()||select>2||select<1) {
			cin.ignore();
			cout << "�����������������룺";
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
		cout << "����ɹ����������Ϊ��" << endl;
		this->savefile();
		this->show_emp();

	}
}

void workermanager::clean_file()
{
	if (this->_fileisempty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "ȷ�������" << endl;
		cout << "  0-ȷ��" << endl;
		cout << "  1-ȡ��" << endl;
		cout << "���������ѡ��";
		int select;
		cin >> select;
		while (cin.fail() || select < 0 || select>1)
		{
			cin.ignore();
			cout << "�����������������룺";
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
			cout << "��ճɹ�" << endl;
			system("pause");
			system("cls");
		}
		else {
			cout << "ȡ���ɹ�" << endl;
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