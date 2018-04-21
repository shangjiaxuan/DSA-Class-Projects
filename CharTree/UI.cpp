#include "UI.h"

using namespace std;

void UI::ignore_space(std::istream& ist) {
	char c;
	ist.get(c);
	while(c==' ') {
		ist.get(c);
	}
	ist.putback(c);
}



void UI::UI_main() {
	string cmd;
	cout << "Please enter a command:" << endl;
	cin >> cmd;
	ignore_space(cin);
	if(cmd=="add") {
		add();
	}
	else if(cmd=="del") {
		del();
	}
	else if(cmd=="list") {
		list();
	}
	else if(cmd=="exit") {
		on = false;
	}
	else if(cmd=="ntoken") {
		cin >> cmd;
		base.ntoken(cmd);
	}
	else {
		throw runtime_error("UI::UI_main: unknown command!");
	}
}

void UI::add() {
	string cmd;
	getline(cin, cmd);
	if(add_file(cmd)) {
		return;
	}
	add_manual(cmd);
}

bool UI::add_file(string cmd) {
	ifstream ifs;
	string path = parse_path(cmd);
	ifs.open(path);
	if(ifs) {
		add_stream(ifs);
		ifs.close();
		return true;
	}
	return false;
}

void UI::add_manual(string cmd) {
	cout << "Adding book " << cmd << endl;
	add_string(cmd);
}

void UI::add_stream(istream& ist) {
	string cmd;
	while(!ist.eof()) {
		getline(ist, cmd);
		if(cmd!="") {
			add_string(cmd);
		}
	}
}

void UI::add_string(std::string line) {
	//有序号的可能
	istringstream iss(line);
	int index; string name;
	if(iss>>index) {
		getline(iss, name);
		name = parse_bookname(name);
		base.add(index, name);
		return;
	}
	name = parse_bookname(line);
	base.add(name);
}

void UI::del() {
	string cmd;
	getline(cin, cmd);
	if(del_file(cmd)) {
		return;
	}
	del_manual(cmd);
}

bool UI::del_file(std::string cmd) {
	ifstream ifs;
	string path = parse_path(cmd);
	ifs.open(path);
	if (ifs) {
		del_stream(ifs);
		ifs.close();
		return true;
	}
	return false;
}

void UI::del_manual(std::string cmd) {
	cout << "Deleting book " << cmd << endl;
	del_string(cmd);
}

void UI::del_stream(std::istream& ist) {
	string cmd;
	while (!ist.eof()) {
		getline(ist, cmd);
		if (cmd != "") {
			del_string(cmd);
		}
	}
}

//为了用户操作简便，目前不支持数字开头的书名
void UI::del_string(std::string line) {
	istringstream iss(line);
	int index; string name;
	if (iss >> index) {
		base.del(index);
		return;
	}
	name = parse_bookname(line);
	base.del(name);
}

void UI::list() {
	string cmd;
	cin >> cmd;
	ignore_space(cin);
	if(cmd=="book") {
		list_book();
	}
	else if(cmd=="index") {
		list_index();
	}
}

void UI::list_book() {
	char c;
	cin >> c;
	if(c=='>') {
		ofstream ofs;
		string s;
		ignore_space(cin);
		cin >> s;
		ofs.open(s);
		if(!ofs) {
			throw runtime_error("UI::list_book: cannot open file for output!");
		}
		list_book_stream(ofs);
		ofs.close();
	}
	else {
		list_book_stream(cout);
	}
}

void UI::list_index() {
	char c;
	cin >> c;
	if (c == '>') {
		ofstream ofs;
		string s;
		ignore_space(cin);
		cin >> s;
		ofs.open(s);
		if (!ofs) {
			throw runtime_error("UI::list_index: cannot open file for output!");
		}
		list_index_stream(ofs);
		ofs.close();
	}
	else {
		list_index_stream(cout);
	}
}

void UI::list_book_stream(std::ostream& ost) {
	ost << "The following is the information of all the books in repository:\n" << endl;
	base.print_booklist(ost);
}

void UI::list_index_stream(std::ostream& ost) {
	ost << "The following are all the indexes in repository:\n" << endl;
	base.print_index(ost);
}

string UI::parse_bookname(string line) {
	istringstream iss(line);
	string current;
	string name("");
	while (iss) {
		current = "";
		iss >> current;
		name.append(current);
		name.push_back(' ');
	}
	name.pop_back();
	return name;
}

string UI::parse_path(string line) {
	string path;
	istringstream iss(line);
	char current;
	iss.get(current);
	while (current == ' ') {
		iss.get(current);
	}
	iss.putback(current);
	while (iss) {
		iss.get(current);
		switch (current) {
		case '\"':
			iss.get(current);
			while (current != '\"') {
				path.push_back(current);
				iss.get(current);
			}
			break;
		default:
			path.push_back(current);
			iss.get(current);
		}
	}
	return path;
}
