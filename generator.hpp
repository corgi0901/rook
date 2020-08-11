#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <vector>
#include "rook.hpp"

using namespace std;

class Generator
{
private:
	vector<Operation> operations;
	vector<Variable> vars;
	int offset;
	int label;

	void gen(Node* node);
	void gen_var(Node* node);
	bool findVar(const char* name, int len);
	Variable getVar(const char* name, int len);

public:
	vector<Operation> codegen(vector<Node*> &nodes);
};

#endif // GENERATOR_H_
