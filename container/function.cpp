#include <iostream>
#include <string>
#include "function.hpp"

using namespace std;

int Function::funcNum = 0;

Function::Function(string name)
{
	this->name = name;
	this->label = funcNum++;

	vars.clear();
};

void Function::addVar(string name)
{
	Variable* var = new Variable(name, vars.size());
	vars.push_back(var);
};

bool Function::hasVar(string name)
{
	for(Variable* var : vars){
		if(name == var->name){
			return true;
		}
	}
	return false;
};

void Function::print(void)
{
	cout << "func" << label << " : " << name << endl;
	for(Variable* var : vars){
		var->print();
	}
};
