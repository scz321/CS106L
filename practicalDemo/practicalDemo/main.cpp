
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

	return;


}
class MyClass {
public:
	MyClass(const std::string& name) : name(name) {}

	void setName(const std::string& newName) {
		name = newName;
	}

	std::string getName() const {
		return name;
	}

private:
	std::string name;
};


using namespace std;
int main() {
	//keyWordsCount();
	//EmailAddressTest();
	//IsPalindromesTextTest();
	//SmartPointerTest();
	
	
	//callFunction(5.0, myFunction);  // 这里传递的是函数指针
	//getIntegerTest();
	//functorTest();
	
	
	//temp();
	MyClass t1("施成志");
	t1.setName("hhh");
	cout << t1.getName() << endl;

	const MyClass t2("abc");
	t2.setName("hhh");
	cout << t2.getName() << endl;


	return 0;
}






