#include <cstring>
#include <vector>
#include "generator.hpp"
#include "rook.hpp"

using namespace std;

void Generator::gen(Node* node)
{
	switch(node->kind){
		case ND_NUM:
			operations.push_back( Operation{ OP_PUSH, node->val } );
			break;

		case ND_ADD:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_ADD, REG_GR0, REG_GR1 } );

			break;

		case ND_SUB:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_SUB, REG_GR1, REG_GR0 } );

			break;

		case ND_MUL:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_MUL, REG_GR0, REG_GR1 } );

			break;

		case ND_DIV:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_DIV, REG_GR1, REG_GR0 } );

			break;

		default:
			break;
	}
};

vector<Operation> Generator::codegen(vector<Node*> &nodes)
{
	vector<Node*>::iterator node;

	for(node = nodes.begin(); node != nodes.end(); node++){
		gen(*node);
		operations.push_back( Operation{ OP_POP, REG_GR0 } );
	}

	return operations;
};
