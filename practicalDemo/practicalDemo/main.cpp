
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>

#include "keyWordsCount.hpp"
#include "DFA.hpp"
#include "PalindromesJudge.hpp"
#include "smartPtr.hpp"
#include "getInteger.hpp"
#include "functor.hpp"

using namespace std;

void temp() {


	std::map<int, std::string> myMap;
	myMap[1] = "one";
	myMap[2] = "two";
	myMap[3] = "three";

	for (const auto& iter : myMap) {
		// 使用结构化绑定获取键和值
		auto [key, value] = iter;
		std::cout << "Key: " << key << ", Value: " << value << std::endl;
	}


}


using namespace std;
int main() {
	//keyWordsCount();
	//EmailAddressTest();
	//IsPalindromesTextTest();
	//SmartPointerTest();
	
	
	//callFunction(5.0, myFunction);  // 这里传递的是函数指针
	//getIntegerTest();
	//functorTest();
	temp();

	return 0;
}






