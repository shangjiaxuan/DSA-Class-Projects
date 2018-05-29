#include "BinSort.h"

using namespace std;


//实际上可以一边输入一边生成，但这里用了先输入后排序的方法
BinSort::BinSort() {
	string cmd;
	cout << "Please specify the indexes you wish to sort:\n";
	getline(cin, cmd);
	istringstream iss0(cmd);
	int num;
	if (iss0 >> num) {
		istringstream iss1(cmd);
		istringstream iss2(cmd);
		init(iss1);
		sort(iss2);
	}
	else {
		cmd = parse_path(cmd);
		ifstream ifs;
		ifs.open(cmd);
		if (!ifs) {
			throw runtime_error("BinSort::BinSort(): Cannot load specified indexes!");
		}
		init(ifs);
		ifs.close();
		ifs.open(cmd);
		if (!ifs) {
			throw runtime_error("BinSort::BinSort(): Cannot reopen secified file!");
		}
		sort(ifs);
		ifs.close();
	}
}

void BinSort::init(istream& ist) {
	int temp;
	while (ist >> temp) {
		size++;
	}
	data = new node[size];
};

void BinSort::sort(istream& ist) {
	int num;
	size_t i{ 0 };
	while (ist >> num) {
		data[i].data = num;
		add(i);
		i++;
	}
}

void BinSort::add(size_t added) {
	size_t root=find_parent_node(this->root, data[added].data);
	if (data[added].data < data[root].data) {
		unbalance unb = add_left(root, added);
		if (unb.subtree<0) {
			return;
		}
		else {
			parse_unbalance(unb);
		}
	}
	else if (data[added].data >= data[root].data) {
		unbalance unb = add_right(root, added);
		if (unb.subtree<0) {
			return;
		}
		else {
			parse_unbalance(unb);
		}
	}
}

size_t BinSort::find_parent_node(size_t root, int index) {
	size_t trace;
	while (root >= 0) {
		if (index < data[root].data) {
			trace = root;
			root = data[root].lchild;
			continue;
		}
		if (index >= data[root].data) {
			trace = root;
			root = data[root].rchild;
			continue;
		}
	}
	return trace;
}

BinSort::unbalance BinSort::add_left(size_t subtree, size_t added) {
	data[subtree].lchild = added;
	data[added].parent = subtree;
	data[added].depth = 1;
	return find_smallest_unbalance(subtree,false);
}

BinSort::unbalance BinSort::add_right(size_t subtree, size_t added) {
	data[subtree].rchild = added;
	data[added].parent = subtree;
	data[added].depth = 1;
	return find_smallest_unbalance(subtree,true);
}

BinSort::unbalance BinSort::find_smallest_unbalance(long long start,bool current) {
	unbalance rtn;
	rtn.current = current;
	rtn.child = false;
	while (start >= 0 && (data[data[start].lchild].depth != data[data[start].rchild].depth)){
		if (data[data[start].lchild].depth > data[data[start].rchild].depth) {
			data[start].depth = data[data[start].lchild].depth + 1;
			if ((data[data[start].lchild].depth - data[data[start].rchild].depth) == 1) {
				start = data[start].parent;
				rtn.child = rtn.current;
				if (data[data[start].parent].rchild == start) {
					rtn.current = true;
				}
				else {
					rtn.current = false;
				}
			}
			else {
				return rtn;
			}
		}
		else {
			data[start].depth = data[data[start].rchild].depth + 1;
			if ((data[data[start].rchild].depth - data[data[start].lchild].depth) == 1) {
				start = data[start].parent;
				rtn.child = rtn.current;
				if (data[data[start].parent].rchild == start) {
					rtn.current = true;
				}
				else {
					rtn.current = false;
				}
			}
			else {
				return rtn;
			}
		}
	}
	return {false,false,-1};
}

void BinSort::parse_unbalance(unbalance unb) {
	if (unb.current == false && unb.child == false) {
		if (data[unb.subtree].parent < 0) {
			root = data[unb.subtree].lchild;
			data[data[unb.subtree].lchild].parent = -1;
		}
		else {
			if (data[data[unb.subtree].parent].lchild == unb.subtree) {
				data[data[unb.subtree].parent].lchild= data[unb.subtree].lchild;
				data[data[unb.subtree].lchild].parent = data[unb.subtree].parent;
			}
			else if (data[data[unb.subtree].parent].rchild == unb.subtree) {
				data[data[unb.subtree].parent].rchild = data[unb.subtree].lchild;
				data[data[unb.subtree].lchild].parent = data[unb.subtree].parent;
			}
			else {
				throw runtime_error("BinSort::parse_unbalance(unbalance unb): Child-parent mismatch!");
			}
		}
		data[unb.subtree].parent = data[unb.subtree].lchild;
		data[unb.subtree].lchild = data[data[unb.subtree].lchild].rchild;
		return;
	}
	if (unb.current == true && unb.child == true) {
		if (data[unb.subtree].parent < 0) {
			root = data[unb.subtree].rchild;
			data[data[unb.subtree].rchild].parent = -1;
		}
		else {
			if (data[data[unb.subtree].parent].lchild == unb.subtree) {
				data[data[unb.subtree].parent].lchild = data[unb.subtree].rchild;
				data[data[unb.subtree].rchild].parent = data[unb.subtree].parent;
			}
			else if (data[data[unb.subtree].parent].lchild == unb.subtree) {
				data[data[unb.subtree].parent].lchild = data[unb.subtree].lchild;
				data[data[unb.subtree].lchild].parent = data[unb.subtree].parent;
			}
			else {
				throw runtime_error("BinSort::parse_unbalance(unbalance unb): Child-parent mismatch!");
			}
		}
		data[unb.subtree].parent = data[unb.subtree].rchild;
		data[unb.subtree].rchild = data[data[unb.subtree].rchild].lchild;
		return;
	}





}