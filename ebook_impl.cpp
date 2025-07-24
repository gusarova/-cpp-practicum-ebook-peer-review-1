
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class EBookTracker {
public:
	EBookTracker() {
		user_pages_ = vector<int>(MAX_USERS_COUNT + 1);
		page_readers_ = vector<int>(MAX_PAGES_COUNT + 1);
	}
	double Cheer(int user_id) const {
		int page_number = user_pages_[user_id];
		if (page_number == 0) {
			return 0;
		}
		if (users_counter == 1) {
			return 1;
		}
		double less_page_readers = users_counter - page_readers_[page_number];
		return less_page_readers / (users_counter - 1);
	}
	void Read(int user_id, int page_num) {
		int prev_page = user_pages_[user_id];
		if (prev_page == 0) {
			users_counter++;
		}
		user_pages_[user_id] = page_num;
		for (size_t id = prev_page + 1; id <= page_num; ++id) {
			page_readers_[id]++;
		}
	}
private:
	static const int MAX_USERS_COUNT = 100'000;
	static const int MAX_PAGES_COUNT = 1000;
	std::vector<int> user_pages_;
	std::vector<int> page_readers_;
	int users_counter = 0;
};


class EBookProcessor {
public:
	EBookProcessor(std::istream& input, std::ostream& output) :input_(input), output_(output) {
	}
	void ProcessCommand() {
		std::string command = ReadCommand();
		if (command == "CHEER") {
			ProcessCheer();
		}
		else {
			ProcessRead();
		}
	}

private:
	std::string ReadCommand() {
		std::string command;
		input_ >> command;
		return command;
	}
	void ProcessCheer() {
		int user_id;
		input_ >> user_id;
		output_ << tracker_.Cheer(user_id) << "\n";
	}
	void ProcessRead() {
		int user_id = 0;
		int page_num = 0;
		input_ >> user_id >> page_num;
		tracker_.Read(user_id, page_num);
	}
	std::istream& input_;
	std::ostream& output_;
	EBookTracker tracker_{};
};


int main() {
	int count = 0;
	std::cin >> count;
	std::cout << std::setprecision(6);
	EBookProcessor processor{ std::cin, std::cout };
	for (size_t i = 0; i < count; ++i) {
		processor.ProcessCommand();
	}
}