#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <vector>
#include "rook.hpp"

using namespace std;

class Generator
{
private:
	vector<Operation> operations;

public:
	vector<Operation> codegen(Node* node);
};

#endif // GENERATOR_H_
