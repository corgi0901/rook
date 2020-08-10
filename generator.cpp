#include <cstring>
#include <iostream>
#include <vector>
#include "generator.hpp"
#include "rook.hpp"

using namespace std;

bool Generator::findVar(const char* name, int len)
{
	vector<Variable>::iterator itr;

	for(itr = vars.begin(); itr != vars.end(); itr++){
		if(strncmp(name, itr->name, len) == 0){
			return true;
		}
	}

	return false;
};

Variable Generator::getVar(const char* name, int len)
{
	vector<Variable>::iterator itr;

	for(itr = vars.begin(); itr != vars.end(); itr++){
		if(strncmp(name, itr->name, len) == 0){
			break;
		}
	}

	return *itr;
};

void Generator::gen_var(Node* node)
{
	if(findVar(node->name, node->len)){
		Variable var = getVar(node->name, node->len);
		operations.push_back( Operation{ OP_PUSH_I, var.offset } );
	}
	else{
		Variable var = { node->name, node->len, offset++ };
		vars.push_back(var);
		operations.push_back( Operation{ OP_PUSH_I, var.offset } );
	}
};

void Generator::gen(Node* node)
{
	switch(node->kind){
		case ND_NUM:
			operations.push_back( Operation{ OP_PUSH_I, node->val } );
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

		case ND_EQ:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_EQ, REG_GR1, REG_GR0 } );

			break;

		case ND_NEQ:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_NEQ, REG_GR1, REG_GR0 } );

			break;

		case ND_LESS:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_LESS, REG_GR1, REG_GR0 } );

			break;

		case ND_EQLESS:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_EQLESS, REG_GR1, REG_GR0 } );

			break;

		case ND_ASSIGN:
			gen_var(node->left);
			gen(node->right);

			operations.push_back( Operation{ OP_POP, REG_GR1 } );
			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_STORE, REG_GR0, REG_GR1 } );
			operations.push_back( Operation{ OP_PUSH, REG_GR1 } );

			break;

		case ND_IDENT:
			gen_var(node);

			operations.push_back( Operation{ OP_POP, REG_GR0 } );
			operations.push_back( Operation{ OP_LOAD, REG_GR1, REG_GR0 } );
			operations.push_back( Operation{ OP_PUSH, REG_GR1 } );

			break;

		default:
			break;
	}
};

vector<Operation> Generator::codegen(vector<Node*> &nodes)
{
	offset = 0;
	vector<Node*>::iterator node;

	for(node = nodes.begin(); node != nodes.end(); node++){
		gen(*node);
		operations.push_back( Operation{ OP_POP, REG_GR0 } );
	}

	return operations;
};
