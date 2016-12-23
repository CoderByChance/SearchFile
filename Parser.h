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
	//thread parsing_thread_handle;
	multimap<string, int> symbol_table;
public:
	Parser(const string& file_path);
	~Parser();	
	void start();	
	void searchResult(string& token);
};
