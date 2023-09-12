#pragma once



#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>
using namespace std;

bool IsNotAlphaOrSpace(char ch) {
	return !isalpha(ch) && !isspace(ch);
}
bool IsPalindromesText(string input) {
	//erase all of the punctuations 这里假设回文只考虑字母和数字，不考虑特殊字符
	//input.erase(input.begin(), remove_if(input.begin(), input.end(), isalnum));
	input.erase(remove_if(input.begin(), input.end(),
		[](char c) { return !isalnum(static_cast<unsigned char>(c)); }),
		input.end());

	transform(input.begin(), input.end(), input.begin(), toupper);
	cout << "processed text:" << endl;
	cout << input << endl;
	cout << "==========================" << endl;

	return equal(input.begin(), input.begin() + input.size() / 2, input.rbegin());

}

void IsPalindromesTextTest() {
	cout << "请输入文本的路径：(eg:PalindromesText.txt)";
	string fName;
	cin >> fName;
	ifstream input(fName);

	string text;
	stringstream ss;
	string line;
	while (getline(input, line)) {
		ss << line;
	}
	text = ss.str();

	cout << "judgement result:" << IsPalindromesText(text) << endl;

}