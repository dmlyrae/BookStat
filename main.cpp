#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

const int MaxCount = 100000;
const int MaxPages = 1000;
unordered_map<string, int> ActionsTypes = {
	{"READ", 1},
	{"CHEER", 2}
};

class BookStat {
public:

	BookStat()
		: peoples_(MaxCount + 1, -1)
		, pages_(MaxPages + 1, 0)
	{}
	
	double Cheer(int user_id) {

		if (user_id >= peoples_.size()) {
			throw logic_error("wrong id");
		}

		// User_id ничего не читал
		if (peoples_[user_id] == -1) {
			return 0.0;
		}

		// У книги только один читатель
		if (pages_[0] == 1) {
			return 1.0;
		}

		double total_pages = (pages_[0] - 1) * 1.0;
		double read_pages = (pages_[0] - pages_[peoples_[user_id]]) * 1.0;

		return (read_pages / total_pages);
	}

	void Read(int user_id, int page) {

		if (page < 0 || page > pages_.size()) {
			return;
		}

		auto it = pages_.begin() + peoples_[user_id] + 1;
		auto end = pages_.begin() + std::min(page + 1, static_cast<int>(pages_.size()));

		while (it != end) {
			++(*it++);
		}

		peoples_[user_id] = page;
	}
	
private:
	vector<int> peoples_;
	vector<int> pages_;
};

void ProcessQueries(BookStat& book_stat, istream& input, ostream& out) {
	int action_count;
	input >> action_count;

	while (action_count > 0) {
		string action;
		int user_id;
		input >> action >> user_id;

		switch (ActionsTypes[action]) {
			case 1: {
				int page;
				input >> page;
				book_stat.Read(user_id, page);
				break;
			}
			case 2: {
				out << book_stat.Cheer(user_id) << endl;
				break;
			}
			default:
				throw logic_error("unknown error");
				break;
		}
		--action_count;
	}
}

int main() {

	BookStat book_stat;
	ProcessQueries(book_stat, cin, cout);
	
	return 0;
}