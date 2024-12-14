#include "error.hpp"
#include "context/context.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>

void error::emit_err(std::ifstream& in) const {
	if(is_warning_) {
		std::cerr << "\x1b[1;35mWARNING:\x1b[0m ";
	}
	else {
		std::cerr << "\x1b[31mERROR:\x1b[0m ";
	}
	std::cout << message_ << std::endl;
	
	//print error line of file ...
	std::string temp;
	int i = 1;
	int reserve_width = [](int num) 
		{
		int length = 1;
        while (num >= 10) {
            num /= 10;
            ++length;
        }
        return length;
		}(loc_.last_line);

	while(std::getline(in , temp)) {
		if(i >= loc_.first_line && i <= loc_.last_line) {
			std::cout << std::setw(reserve_width) << i << "|" << "\033[4m" << temp << "\033[0m" << std::endl;
		}
		else if(i > loc_.last_line) {
			break;
		}
		i++;
	}

	std::cout << std::endl;
}

namespace errors{
	namespace {
		std::vector <const error*> err_list;
	}

	void add_err(const error *err) {
		if(err) err_list.push_back(err);
	}

	int get_err_count() {
		return std::count_if(err_list.begin() , err_list.end() , [](const error * e)
			{return !e->check_warning();});
	}

	void emit_all_err(std::ifstream& in) {
		for(int i = 0 ; i < (int)err_list.size() ; i++) {
			in.seekg(0);
			if(err_list[i] != nullptr) err_list[i]->emit_err(in);
		}
	}

	//---- fatal error functions ----//
	void die(std::string message) {
		std::cerr << message << std::endl;
		cleanup();
		exit(1);
	}

	void cleanup() {
		if (ir != nullptr) delete ir;
		context::free();
		
		for(int i = 0 ; i < (int)err_list.size() ; i++) {
			if(err_list[i] != nullptr) delete err_list[i];
		}
	}
}

