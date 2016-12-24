#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

Parser::Parser(const string & _file_path, const char* _delim) : file_path(_file_path), delimiters(_delim) {}

Parser::~Parser() { stream.close(); }

void Parser::start()
{
	stream.open(file_path.c_str(), ios::in);
	if (!stream.is_open()) throw "file not found";

	struct Message {
		string text; int line;
		Message(string& _text, int l) : text(_text), line(l) {}		
		Message(Message&& m) {
			text = move(m.text);
			line = m.line;			
		}
	};

	vector<queue<Message> > vec_msg_queue(10);	
	bool end_of_file = false;
	mutex mut;	

	auto parse_lambda = [&](int id) {
		while (!end_of_file) {			
			lock_guard<mutex> lock(mut);
			if (!vec_msg_queue[id].empty()) {												
				Message m = move(vec_msg_queue[id].front());
				vec_msg_queue[id].pop();
				while (m.text.size()) {
					symbol_table.insert(make_pair(getNextToken(m.text, delimiters), m.line));
				}
			}//else std::this_thread::yield();
		}
	};
	thread read_thread, parse_thread[10];			
	
	for (int i = 0; i < 10; i++) {
		parse_thread[i] = thread(parse_lambda, i);
	}

	read_thread = thread([&]() { 
						
		int line_no = 0;
		while (!stream.eof()) {			
			//std::unique_lock<std::mutex> lck(mut);
			lock_guard<mutex> lock(mut);
			string text;
			getline(stream, text); ++line_no;			
			vec_msg_queue[line_no % 10].push(move(Message(text, line_no)));					
		}
		end_of_file = true;
	});
	read_thread.join();	
	for (int i = 0; i < 10; i++) {		
		parse_thread[i].join();
	}
}

void Parser::query(string & token)
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
