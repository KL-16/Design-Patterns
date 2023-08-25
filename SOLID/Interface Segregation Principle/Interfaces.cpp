#include <iostream>
#include <vector>

struct Document {};

struct IPrinter {
	virtual void print(std::vector<Document*> docs) = 0;
};

struct IScanner {
	virtual void scan(std::vector<Document*> docs) = 0;
};

struct Printer : IPrinter {
	void print(std::vector<Document*> docs) override {
		std::cout << "Printing" << std::endl;
	}
};

struct Scanner : IScanner {
	void scan(std::vector<Document*> docs) override {
		std::cout << "Scanning" << std::endl;
	}
};

struct IMachine : IPrinter, IScanner {
};

struct Machine : IMachine {
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter& printer, IScanner& scanner) : printer{printer}, scanner{scanner} {}

	void print(std::vector<Document*> docs) override {
		printer.print(docs);
	}

	void scan(std::vector<Document*> docs) override {
		scanner.scan(docs);
	}
};

int main() {
	Printer printer;
	Scanner scanner;
	Machine machine(printer, scanner);
	Document document;
	std::vector<Document*> docs;
	docs.push_back(&document);
	machine.print(docs);
	machine.scan(docs);
	return 0;
}