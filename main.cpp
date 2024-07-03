#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Book {
public:
	void AddUser(int id, int page) {
		if (!user_page_.count(id)) {
			user_page_[id] = page;
			page_users_[page].insert(id);
		}
		else {
			page_users_.at(user_page_.at(id)).erase(id);
			if (page_users_.at(user_page_.at(id)).empty()) {
				page_users_.erase(user_page_.at(id));
			}
			page_users_[page].insert(id);
			user_page_.at(id) = page;
		}
	}
	double GetCheer(int id) {
		if (!user_page_.count(id)) {
			return 0;
		}
		if (user_page_.size() == 1) {
			return 1;
		}
		const auto& iter = page_users_.find(user_page_.at(id));
		int count = 1;
		for (auto i = page_users_.begin(); i != iter; ++i) {
			count += i->second.size();
		}
		return (count * 1.0 - 1) / (user_page_.size() - 1);
	}

private:
	map<int, set<int>> page_users_;
	map<int, int> user_page_;
};




void RequestProcessing(istream& input, ostream& output) {
	Book one;
	int count_commfnd;
	input >> count_commfnd;
	for (int i = 0; i < count_commfnd; ++i) {
		string command;
		input >> command;
		if (command == "READ") {
			int id, page;
			input >> id >> page;
			one.AddUser(id, page);
		}
		else if (command == "CHEER") {
			int id;
			input >> id;
			output << one.GetCheer(id) << endl;
		}
	}

}

int main() {
	RequestProcessing(cin, cout);
	return 0;
}
