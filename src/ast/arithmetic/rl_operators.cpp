#include "rl_operators.hpp"
#include <iostream>

void add::generateIR() const {

}

void add::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────add: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void sub::generateIR() const {

}

void sub::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────sub: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void mul::generateIR() const {

}

void mul::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────mul: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void divi::generateIR() const {

}

void divi::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────div: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void modulo::generateIR() const {

}

void modulo::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────modulo: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void left_shift::generateIR() const {

}

void left_shift::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────left_shift: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void right_shift::generateIR() const {

}

void right_shift::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────right_shift: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void less_than::generateIR() const {

}

void less_than::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────less_than: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void greater_than::generateIR() const {

}

void greater_than::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────greater_than: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void less_eq_than::generateIR() const {

}

void less_eq_than::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────less_then_eq: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void greater_eq_than::generateIR() const {

}

void greater_eq_than::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────greater_than_eq: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void equality::generateIR() const {

}

void equality::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────equality: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void not_equal::generateIR() const {

}

void not_equal::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────not equal: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void andop::generateIR() const {

}

void andop::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────and: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void xorop::generateIR() const {

}

void xorop::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────xor: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void orop::generateIR() const {

}

void orop::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────or: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void log_andop::generateIR() const {

}

void log_andop::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────logical and: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

void log_orop::generateIR() const {

}

void log_orop::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────logical or: " << std::endl;
	if(l_value_ != nullptr) l_value_->printAST(depth + 1);
	if(r_value_ != nullptr) r_value_->printAST(depth + 1);
}

