#ifndef INTERM_REPR_HPP
#define INTERM_REPR_HPP

class IR;
class block;

//global Intermediate representation variable
extern IR *ir;

//IR class which encapsulates all the blocks and methods for 
//	--storing the IR
//	--optimising the IR
//	--generating assmebly from IR
class IR {

};

//block base class with certain innate block functions
class block {

};

//particular block e.g. function declaration type?
//others might include jumps
//or three address code sections
class functional_block : public block {

};



#endif
