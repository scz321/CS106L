#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


/*
GetInteger预期功能：

- 参数：输入流对象is
- 返回：从is中读取到的整数
- 仅以回车为终止条件，需要获得一个完整的整数，完整整数的前后允许空格存在

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
			//如果后面有空格似乎也会被识别成remains？---实践证明不会，scanner会忽略空格而不是读取空格，这也
			//和我们预期的流提取运算符的行为一致
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