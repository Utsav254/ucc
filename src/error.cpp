#include "error.hpp"
#include "context.hpp"
#include <algorithm>
#include <iostream>

namespace errors{
	namespace {
		std::vector <error*> err_list;
	}

	void add_err(error *err) {
		err_list.push_back(err);
	}

	int get_err_count() {
		//is a fancy iterator and lambda function really necassary?
		return std::count_if(err_list.begin() , err_list.end() , [](error * e)
			{return !e->check_warning();});
	}

	void emit_all_err() {
		for(int i = 0 ; i < (int)err_list.size() ; i++) {
			if(err_list[i] != nullptr) err_list[i]->emit_err();
		}
	}

	//---- fatal error functions ----//
	void die(std::string message) {
		std::cerr << "\x1b[31mERROR:\x1b[0m "<< "\n";
		std::cerr << message << std::endl;
		cleanup();
		exit(1);
	}

	void cleanup() {
		if (root_node != nullptr) delete root_node;
		if (ir != nullptr) delete ir;
		context::free();
		
		for(int i = 0 ; i < (int)err_list.size() ; i++) {
			if(err_list[i] != nullptr) delete err_list[i];
		}

	}
}

