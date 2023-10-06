#pragma once

#include <vector>
#include <numeric>
#include <iostream>
//Ҫ�󣺱���vector���������д����½����Сֵ


//��������
class functor {
public:
	
	explicit functor(int lower) :lowBound(lower) {};
	//�ڱ����У�����ֵ��Ȼ��int����Ϊ����ֵ����������accumulate�ĵ�����������
	int operator()(int bestSoFar, int curVal) {
		if (curVal <= lowBound)
			return bestSoFar;
		return bestSoFar < curVal ? bestSoFar : curVal;
	}

private:
	int lowBound;
};


//������ָ�룩
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
