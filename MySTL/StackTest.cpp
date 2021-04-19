#include <iostream>
#include <string>
#include <vector>
#include "MyStack.cpp"

using namespace std;

bool bracket_matching(string& str) {
	const string left_bracket = "([{";
	const string right_bracket = ")]}";
	MyStack<int> s(100);
	int len = str.length();
	for (int i = 0; i < len; i++) {
		char c = str[i];
		//×óÀ¨ºÅ
		if (left_bracket.find(c) != -1) {
			s.push(c);
			continue;
		}
		//ÓÒÀ¨ºÅ
		size_t right_bracket_index = right_bracket.find(c);
		if (right_bracket_index != -1) {
			if (s.empty()) {
				return false;
			}
			size_t left_bracket_index = left_bracket.find(s.pop());
			if (right_bracket_index != left_bracket_index) {
				return false;
			}
		}
	}
	return s.empty();
}

void testBracketMatching() {
	MyStack<int> s;
	for (int i = 0; i < 105; i++) {
		s.push(i);
	}
	for (; !s.empty();) {
		cout << s.pop() << endl;
	}
	vector<string> strs{ "()()",")()(","([]){[[]]()}" };
	for (int i = 0; i < strs.size(); i++) {
		cout << boolalpha << strs[i] << ": " << bracket_matching(strs[i]) << endl;
	}
}

void polishCalculator() {
	cout << "Starting polish calculator..." << endl
		 << "Please input numbers and operators" << endl;
	char op;
	int num;
	MyStack<int> s;
	while (cin >> op) {
		if (op == '?') {
			cin >> num;
			s.push(num);
		} else if (op == '=') {
			if (s.empty()) {
				throw "Empty stack";
			}
			cout << s.peek() << endl;
		} else if (op == 'q') {
			cout << "Calculation finished" << endl;
			return;
		} else {
			if (s.size() < 2) {
				throw "Not enough numbers";
			}
			int i1 = s.pop(), i2 = s.pop();
			switch (op) {
			case '+':
				s.push(i1 + i2);
				break;
			case '-':
				s.push(i2 - i1);
				break;
			case '*':
				s.push(i1 * i2);
				break;
			case '/':
				s.push(i2 / i1);
				break;
			default:
				throw "Illegal operator";
			}
		}
	}
}

string conversion(int dec, int radix) {
	string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	MyStack<int> s;
	do {
		s.push(dec % radix);
		dec /= radix;
	} while (dec > 0);
	string res = "";
	while (!s.empty()) {
		res.push_back(chars[s.pop()]);
	}
	return res;
}