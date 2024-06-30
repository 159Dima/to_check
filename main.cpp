#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void RequestProcessing(istream& input, ostream& output) {
	string str;
	map<int, set<int>> pages_;
	map<int, int> iduser_page;
	int count_commfnd;
	input >> count_commfnd;
	for (int i = 0; i < count_commfnd; ++i) {
		string command;
		input >> command;
		if (command == "READ") {
			int id, page;
			input >> id >> page;
			if (!iduser_page.count(id)) {
				iduser_page[id] = page;
				pages_[page].insert(id);
			}
			else {
				pages_.at(iduser_page.at(id)).erase(id);
				if (pages_.at(iduser_page.at(id)).empty()) {
					pages_.erase(iduser_page.at(id));
				}
				pages_[page].insert(id);
				iduser_page.at(id) = page;
			}
		}
		else if (command == "CHEER") {
			int id;
			input >> id;
			if (!iduser_page.count(id)) {
				output << 0 << endl;
				continue;
			}
			if (iduser_page.size() == 1) {
				output << 1 << endl;
				continue;
			}
			const auto& iter = pages_.find(iduser_page.at(id));
			int count = 1;
			for (auto i = pages_.begin(); i != iter; ++i) {
				count += i->second.size();
			}
			output << (count * 1.0 - 1) / (iduser_page.size() - 1) << endl;
		}
	}

}

int main() {

	RequestProcessing(cin, cout);



	return 0;
}