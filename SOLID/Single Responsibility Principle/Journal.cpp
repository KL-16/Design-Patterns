#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Journal {
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(const std::string& title) : title{ title } {}

	void add(const std::string&);
};

void Journal::add(const std::string& entry) {
	static int count = 1;
	entries.push_back((count++) + ": " + entry);
}

struct PersistenceManager {
	static void save(const Journal& j, const std::string& filename) {
		std::ofstream ofs(filename);
		for (auto& s : j.entries)
			ofs << s << std::endl;
	}
};

int main() {
	Journal journal("My Journal");
	journal.add("some text to be stored.");
	PersistenceManager persistenceManager;
	persistenceManager.save(journal, "My Journal from today.txt");
	return 0;
}