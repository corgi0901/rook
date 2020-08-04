#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <vector>
#include "rook.hpp"

using namespace std;

class Generator
{
private:
	vector<Operation> operations;
	void gen(Node* node);

public:
	vector<Operation> codegen(vector<Node*> &nodes);
};

#endif // GENERATOR_H_
