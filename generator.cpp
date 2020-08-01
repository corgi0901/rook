#include <cstring>
#include <vector>
#include "generator.hpp"
#include "rook.hpp"

using namespace std;

vector<Operation> Generator::codegen(Node* node)
{
	switch(node->kind){
		case ND_NUM:
			operations.push_back( Operation{ OP_PUSH, node->val } );
			break;
		default:
			break;
	}

	return operations;
};
