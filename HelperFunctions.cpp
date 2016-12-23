//#include "stdafx.h"
#include "HelperFunctions.h"

string getNextToken(string& str, const char* delim, int no_of_delim) {
	string token;
	int len = 0;
	bool end_of_string = true;
	for (char ch : str) {

		//check if current 'ch' is a delimiter
		const char* p = delim;
		bool is_ch_delim = false;
		for (int i = 0; i<no_of_delim; i++, p++) {
			if (ch == *p) {
				is_ch_delim = true; break;
			}
		}
		len++;
		if (is_ch_delim) {
			if (token.size() > 0) { str.erase(0, len); end_of_string = false; break; }
		}
		else token.push_back(ch);
	}

	if (end_of_string) str.clear();

	return token;
}
