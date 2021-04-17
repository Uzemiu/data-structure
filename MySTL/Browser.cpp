#include "Browser.h"
#include <string>

void Browser::visit(const string& page) {
	if (!current) {
		LinkedList<string>::push_last(page);
		current = head;
	} else {
		while (current->next != head) {
			LinkedList<string>::remove(current->next);
		}
		LinkedList<string>::push_last(page);
		current = current->next;
	}
}

bool Browser::forward() {
	return current && current->next != head && (current = current->next);
}

bool Browser::back() {
	return current && current != head && (current = current->prev);
}

string Browser::current_page() {
	return current->ele;
}

char Browser::get_command() {
	string available_command = "vfbx";
	char c;
	while (cin >> c) {
		c = tolower(c);
		if (available_command.find(c) != available_command.npos) {
			break;
		}
		cout << "命令不存在，请重新输入:" << flush;
	}
	return c;
}

void Browser::run_test() {
	cout << "请输入浏览器命令: V<访问新网站>, F<前进>, B<后退>, X<退出>" << endl;
	Browser browser;
	string page;
	for (char c = get_command();; c = get_command()) {
		bool success = true;
		switch (c) {
		case 'v':
			cout << "请输入新的网址：" << flush;
			cin >> page;
			browser.visit(page);
			cout << "当前网址是：" << browser.current_page() << endl;
			break;
		case 'b':
			if (browser.back()) {
				cout << "当前网址是：" << browser.current_page() << endl;
			} else {
				cout << "无法后退！" << endl;
			}
			break;
		case 'f':
			if (browser.forward()) {
				cout << "当前网址是：" << browser.current_page() << endl;
			} else {
				cout << "无法前进！" << endl;
			}
			break;
		case 'x':
			return;
		}
	}
}
