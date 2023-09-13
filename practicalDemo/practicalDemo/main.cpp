
#include <iostream>
#include "keyWordsCount.hpp"
#include "DFA.hpp"
#include "PalindromesJudge.hpp"
#include "smartPtr.hpp"
#include <stdexcept>

void setAge(int age) {
	if (age < 0) {
		throw invalid_argument("Age cannot be negative");
	}
	// ... ÆäËû´úÂë
}


using namespace std;
int main() {
	//keyWordsCount();
	//EmailAddressTest();
	//IsPalindromesTextTest();
	//SmartPointerTest();
	try {
		setAge(-5);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument: " << ia.what() << std::endl;
	}

	return 0;
}






