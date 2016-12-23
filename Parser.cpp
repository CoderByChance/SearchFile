//#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <functional>

Parser::Parser(const string & file_path) : file_path(file_path){}

Parser::~Parser() { stream.close(); }

void Parser::start()
{
	stream.open(file_path.c_str(), ios::in);
	if (!stream.is_open()) throw "file not found";

	thread t([&]() {
		std::cout << file_path << " : file parsing started...\n";
		int line_no = 0;
		string text;
		while (!stream.eof()) {
			getline(stream, text);
			++line_no;
			while (text.size()) {
				symbol_table.insert(make_pair(getNextToken(text, " ", 1), line_no));
			}
		}
		cout << "==parsing finished==" << endl;
	});
	t.join();
}

void Parser::searchResult(string & token)
{
	stream.close();
	stream.open("out.txt", ios::out);
	
	auto range = symbol_table.equal_range(token);
	auto it = range.first;
	while (it != range.second) {
		stream << "line_no : " << it->second << endl;
		++it;
	}
}
