#pragma once

#include <iostream>
#include <string>

#include <map>
#include <set>

using namespace std;

struct DFA {
	map<pair<int, char>, int> transitions;
	set<int> acceptingStates;
	int startState;
};

bool SimulateDFA(DFA& d, string input) {
	int currState = d.startState;
	for (string::iterator itr = input.begin(); itr != input.end(); ++itr) {
		cout << "当前状态转移：" << currState << "-->" << d.transitions[make_pair(currState, *itr)] << endl;;
		currState = d.transitions[make_pair(currState, *itr)];
		

	}
	//cout << "currState:" << currState << endl;
	return d.acceptingStates.find(currState) != d.acceptingStates.end();
}



//===========================下面是针对邮箱地址设置的相关内容，上面是通用设计=========
struct DFA LoadEmailDFA() {
	struct DFA ret;
	ret.startState = 0;
	ret.acceptingStates.insert(6);


	//这里反而是最麻烦的地方hhh，打错一个地方就g
	ret.transitions.insert(make_pair(make_pair(0,'a'),1));//注意，这里外层还需要一次make_pair
	ret.transitions.insert(make_pair(make_pair(0, '.'), 7));
	ret.transitions.insert(make_pair(make_pair(0, '@'), 7));

	ret.transitions.insert(make_pair(make_pair(1, 'a'), 1));
	ret.transitions.insert(make_pair(make_pair(1, '@'), 3));
	ret.transitions.insert(make_pair(make_pair(1, '.'), 2));

	ret.transitions.insert(make_pair(make_pair(2, 'a'), 1));
	ret.transitions.insert(make_pair(make_pair(2, '@'), 7));
	ret.transitions.insert(make_pair(make_pair(2, '.'), 7));

	ret.transitions.insert(make_pair(make_pair(3, '@'), 7));
	ret.transitions.insert(make_pair(make_pair(3, '.'), 7));
	ret.transitions.insert(make_pair(make_pair(3, 'a'), 4));

	ret.transitions.insert(make_pair(make_pair(4, '@'), 7));
	ret.transitions.insert(make_pair(make_pair(4, '.'), 5));
	ret.transitions.insert(make_pair(make_pair(4, 'a'), 4));

	ret.transitions.insert(make_pair(make_pair(5, '@'), 7));
	ret.transitions.insert(make_pair(make_pair(5, '.'), 7));
	ret.transitions.insert(make_pair(make_pair(5, 'a'), 6));

	ret.transitions.insert(make_pair(make_pair(6, '.'), 5));
	ret.transitions.insert(make_pair(make_pair(6, 'a'), 6));
	ret.transitions.insert(make_pair(make_pair(6, '@'), 7));

	ret.transitions.insert(make_pair(make_pair(7, '@'), 7));
	ret.transitions.insert(make_pair(make_pair(7, '.'), 7));
	ret.transitions.insert(make_pair(make_pair(7, 'a'), 7));

	return ret;
}


bool IsEmailAddress(string input) {
	DFA emailChecker = LoadEmailDFA(); 
	for (string::iterator itr = input.begin(); itr != input.end(); ++itr) {		
		if (isalnum(*itr))
			*itr = 'a';
		else if (*itr != '.' && *itr != '@')
			return false;
	}
	return SimulateDFA(emailChecker, input);
}

void EmailAddressTest() {
	cout << "请输入邮箱地址:";
	string input;
	cin >> input;
	cout << "judging result:" << IsEmailAddress(input) << endl;
}
