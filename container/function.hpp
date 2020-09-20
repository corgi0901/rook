#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_

#include <string>
#include <vector>
#include "variable.hpp"

using namespace std;

class Function
{
private:
	static int funcNum;

public:
	string name;
	vector<Variable*> vars;
	int label;

	Function(string name);

	void addVar(string name);
	bool hasVar(string name);

	void print(void);
};

#endif // _FUNCTION_HPP_
