#include "BinSort.h"

using namespace std;

BinSort::BinSort() {
	string cmd;
	cout << "Please specify the indexes you wish to sort:\n";
	getline(cin, cmd);
	istringstream iss(cmd);
	int num;
	if (iss >> num) {
		vector<int> temp;
		do {
			temp.push_back(num);
			if (!iss >> num) {
				break;
			}
		} while (true);
		data = new node[temp.size()];
		for (size_t i = 0; i < temp.size(); i++) {
			data[i].data = temp[i];


		}
	}
	else {
		cmd = parse_path(cmd);
		ifstream ifs;
		ifs.open(cmd);
		if (!ifs) {
			throw runtime_error("BinSort::BinSort(): Cannot load specified indexes!");
		}
		int temp;
		size_t size{ 0 };
		while (ifs>>temp) {
			size++;
		}
		ifs.close();
		data = new node[size];
		ifs.open(cmd);
		if (!ifs) {
			throw runtime_error("BinSort::BinSort(): Cannot reopen secified file!");
		}
		size_t i = 0;
		while (ifs >> temp) {
			data[i].data = temp;



			i++;
		}
	}
}

