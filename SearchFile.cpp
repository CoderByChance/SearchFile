// SearchFile.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include "Parser.h"
using namespace std;


int main()
{
	string file_path;
	cout << "Please enter the file path : ";
	cin >> file_path;
	
	Parser parser(file_path);
	parser.start();

	string token;
	cout << "Enter search text : ";
	cin >> token;

	parser.searchResult(token);
	
    return 0;
}
