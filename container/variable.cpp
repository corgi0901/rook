#include <iostream>
#include <string>
#include "variable.hpp"

Variable::Variable(string name, int offset)
{
	this->name = name;
	this->offset = offset;
};

void Variable::print(void)
{
	cout << offset << " : " << name << endl;
};
