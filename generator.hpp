#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <string>
#include <vector>
#include "container/node.hpp"
#include "container/operation.hpp"
#include "container/variable.hpp"

using namespace std;

class Generator
{
private:
	vector<Operation> operations;
	vector<Variable> vars;
	int offset;
	int label;

	void gen(const Node* node);
	void gen_var(const Node* node);
	bool findVar(string name);
	Variable getVar(string name);

public:
	vector<Operation> codegen(vector<Node*> &nodes);
};

#endif // _GENERATOR_H_
