#include <iostream>

#include "LinkedList.cpp"

using namespace std;

void help() {
	cout << endl
		 << "This program allows the user to enter one command" << endl
		 << "(but only one) on each input line." << endl
		 << "For example, if the command S is entered, then" << endl
		 << "the program will serve the front of the queue." << endl
		 << endl
		 << " The valid commands are:" << endl
		 << "A - Append the next input character to the extended queue" << endl
		 << "S - Serve the front of the extended queue" << endl
		 << "R - Retrieve and print the front entry." << endl
		 << "# - The current size of the extended queue" << endl
		 << "C - Clear the extended queue (same as delete)" << endl
		 << "P - Print the extended queue" << endl
		 << "H - This help screen" << endl
		 << "Q - Quit" << endl;
}

char get_command() {
	char command;
	bool waiting = true;
	cout << "Select command and press <Enter>:";
	while (waiting) {
		cin >> command;
		command = tolower(command);
		if (command == 'a' || command == 's' || command == 'r' ||
			command == '#' || command == 'c' || command == 'p' ||
			command == 'h' || command == 'q') waiting = false;
		else {
			cout << "Please enter a valid command:" << endl
				 << "[a] Append [s] Serve [r] Retrieve " << endl
				 << "[#] Size [c] Clear [p] Print [h] Help page" << endl
				 << "[q]uit." << endl;
		}
	}
	return command;
}

bool do_command(char c, LinkedList<char> &q) {
	bool continue_input = true;
	char x;
	switch (c) {
	case 'r':
		if (q.empty()) {
			cout << "The queue is empty." << endl;
		} else {
			cout << endl << "The first entry is: " << q.peek() << endl;
		}
		break;
	case 'a':
		cout << "Please input a char" << endl;
		cin >> x;
		q.push(x);
		break;
	case's':
		if (q.empty()) {
			cout << "The queue is empty." << endl;
		}
		q.pop();
		break;
	case'#':
		cout << "The size of the queue is: " << q.size() << endl;
		break;
	case 'c':
		q.clear();
		cout << "The empty queue with length " << q.size() << endl;
		break;
	case 'h':
		help();
		break;
	case 'p':
		if (q.empty()) {
			cout << "The queue is empty." << endl;
		} else {
			cout << "The queue is: " << flush;
			for (int i = 0; i < q.size(); i++) {
				char ele = q.pop();
				cout << ele << " " << flush;
				q.push(ele);
			}
			cout << endl;
		}
		break;
	case 'q':
		cout << "Queue demonstration finished." << endl;
		continue_input = false;
		break;
	}
	return continue_input;
}

void start_demonstration() {
	//CircularQueue<char> q;
	//help();
	//while (do_command(get_command(), q));
}