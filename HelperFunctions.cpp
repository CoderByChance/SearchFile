#include "stdafx.h"
#include "HelperFunctions.h"

string getNextToken(string& text, const string& delimiters) {
	string token;
	int len = 0;
	bool end_of_text = true;
	for (auto chtext : text) {

		//check if current chtext is a delimiter		
		bool is_delim = false;		
		for(auto delim : delimiters) {
			if (chtext == delim) {
				is_delim = true; break;
			}
		}
		len++;
		if (is_delim) {
			if (token.size() > 0) { text.erase(0, len); end_of_text = false; break; }
		}
		else token.push_back(chtext);
	}

	if (end_of_text) text.clear();

	return token;
}
