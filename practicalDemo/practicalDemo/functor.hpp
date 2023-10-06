#pragma once

#include <vector>
#include <numeric>
#include <iostream>
//要求：遍历vector，返回其中大于下界的最小值


//函数对象
class functor {
public:
	
	explicit functor(int lower) :lowBound(lower) {};
	//在本例中，返回值当然是int，因为返回值是用来更新accumulate的第三个参数的
	int operator()(int bestSoFar, int curVal) {
		if (curVal <= lowBound)
			return bestSoFar;
		return bestSoFar < curVal ? bestSoFar : curVal;
	}

private:
	int lowBound;
};


//函数（指针）
int glbalLowBound = 5;
int function(int bestSoFar, int curVal) {
	if (curVal <= glbalLowBound)
		return bestSoFar;
	return bestSoFar < curVal ? bestSoFar : curVal;
}





void functorTest() {
	std::vector<int> t({ 1,2,3,4,5,6,7 });
	std::cout << std::accumulate(t.begin(), t.end(), std::numeric_limits<int>::max(), function) << std::endl;

}
