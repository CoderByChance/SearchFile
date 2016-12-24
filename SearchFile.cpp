// SearchFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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
	try {
		parser.start();
	}
	catch (const char* exc) { cout << exc << endl; }
	

	string token;
	cout << "Enter search text : ";
	cin >> token;

	parser.query(token);
	
    return 0;
}
