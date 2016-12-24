#pragma once
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <map>
#include "HelperFunctions.h"

using namespace std;

class Parser {	
	string file_path;
	fstream stream;
	const string delimiters;
	multimap<string, int> symbol_table;
public:
	Parser(const string & _file_path, const char* _delim = " \n");
	~Parser();	
	void start();	
	void query(string& token);
};
