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

		case ND_ADD:
			codegen(node->left);
			codegen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_ADD, REG_GR0, REG_GR1 } );

			break;

		case ND_SUB:
			codegen(node->left);
			codegen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_SUB, REG_GR1, REG_GR0 } );

			break;

		default:
			break;
	}

	return operations;
};
