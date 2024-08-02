#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<iomanip>
#include<stdio.h>
#include<fstream>

using namespace std;

inline bool Isalldigit(string str) {
	for (int i = 0; i < sizeof(str); i++) {
		if (!isdigit(str[i]))return false;
	}
	return true;
}

inline void showtime(time_t time) {
	struct tm* p;
	p = localtime(&time);
	printf("%04d.%02d.%02d  %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

inline void m_clean() {
	char cl;
	cl = getchar();
	while ((cl = getchar()) != '\n');
	cin.clear();
	
}
extern int ischioce(string str,int length=1) {
	if (sizeof(str) != length)return -1;
	else if (Isalldigit(str)) {
		return (int)str[0] - 48;
	}
	else {
		return -1;
	}
}
