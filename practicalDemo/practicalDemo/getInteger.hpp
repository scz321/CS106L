#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


/*
GetIntegerԤ�ڹ��ܣ�

- ����������������is
- ���أ���is�ж�ȡ��������
- ���Իس�Ϊ��ֹ��������Ҫ���һ������������������������ǰ������ո����

*/

int getInteger(istream& is) {
	stringstream converter;

	int ret = -1;

	string lineContent="";
	while (getline(is, lineContent)) {
		if (lineContent == "")
			continue;
		else {
			converter << lineContent;
			//��������пո��ƺ�Ҳ�ᱻʶ���remains��---ʵ��֤�����ᣬscanner����Կո�����Ƕ�ȡ�ո���Ҳ
			//������Ԥ�ڵ�����ȡ���������Ϊһ��
			converter >> ret;
			char remains;
			if (converter >> remains) {
				cerr << "Unexpected ending character after Integer!" << endl;
				return -1;
			}
			return ret;
		}
	}
	

	return -1;
}

void getIntegerTest() {
	int t=getInteger(cin);
	cout << "Integer read:" << t << endl;
}