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
		cout << "������ڣ�����������:" << flush;
	}
	return c;
}

void Browser::run_test() {
	cout << "���������������: V<��������վ>, F<ǰ��>, B<����>, X<�˳�>" << endl;
	Browser browser;
	string page;
	for (char c = get_command();; c = get_command()) {
		bool success = true;
		switch (c) {
		case 'v':
			cout << "�������µ���ַ��" << flush;
			cin >> page;
			browser.visit(page);
			cout << "��ǰ��ַ�ǣ�" << browser.current_page() << endl;
			break;
		case 'b':
			if (browser.back()) {
				cout << "��ǰ��ַ�ǣ�" << browser.current_page() << endl;
			} else {
				cout << "�޷����ˣ�" << endl;
			}
			break;
		case 'f':
			if (browser.forward()) {
				cout << "��ǰ��ַ�ǣ�" << browser.current_page() << endl;
			} else {
				cout << "�޷�ǰ����" << endl;
			}
			break;
		case 'x':
			return;
		}
	}
}
