#include <cstring>
#include <iostream>
#include <vector>
#include "container/function.hpp"
#include "container/node.hpp"
#include "container/operation.hpp"
#include "container/variable.hpp"
#include "generator.hpp"
#include "global.hpp"
#include "type.hpp"
#include "vm.hpp"

//#define CODEGEN_DEBUG

using namespace std;

void Generator::gen_var(const Node* node)
{
	if(ND_IDENT != node->kind){
		cerr << "Error : expect identifier" << endl;
		exit(1);
	}

	for(Variable* var : curFunc->vars){
		if(node->name == var->name){
			operations.push_back( Operation( OP_PUSH_I, var->offset ) );
			break;
		}
	}
};

void Generator::gen(const Node* node)
{
	if(node == NULL) return;

	switch(node->kind){
		case ND_NUM:
			operations.push_back( Operation( OP_PUSH_I, node->val ) );
			break;

		case ND_ADD:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_ADD, REG_GR0, REG_GR1 ) );

			break;

		case ND_SUB:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_SUB, REG_GR1, REG_GR0 ) );

			break;

		case ND_MUL:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_MUL, REG_GR0, REG_GR1 ) );

			break;

		case ND_DIV:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_DIV, REG_GR1, REG_GR0 ) );

			break;

		case ND_EQ:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_EQ, REG_GR1, REG_GR0 ) );

			break;

		case ND_NEQ:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_NEQ, REG_GR1, REG_GR0 ) );

			break;

		case ND_LESS:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_LESS, REG_GR1, REG_GR0 ) );

			break;

		case ND_EQLESS:
			gen(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_EQLESS, REG_GR1, REG_GR0 ) );

			break;

		case ND_ASSIGN:
			gen_var(node->left);
			gen(node->right);

			operations.push_back( Operation( OP_POP, REG_GR1 ) );
			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_STORE, REG_GR0, REG_GR1 ) );
			operations.push_back( Operation( OP_PUSH, REG_GR1 ) );

			break;

		case ND_IDENT:
			gen_var(node);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_LOAD, REG_GR1, REG_GR0 ) );
			operations.push_back( Operation( OP_PUSH, REG_GR1 ) );

			break;

		case ND_IF:
			gen(node->left);

			operations.push_back( Operation( OP_POP, REG_GR0 ) );

			if( ND_ELSE == node->right->kind ){
				int lb1 = label++;
				int lb2 = label++;

				operations.push_back( Operation( OP_JZ, REG_GR0, lb1 ) );

				gen(node->right->left);
				operations.push_back( Operation( OP_POP, REG_GR0 ) );	// 評価値の回収
				operations.push_back( Operation( OP_JMP, lb2 ) );

				operations.push_back( Operation( lb1 ) );

				gen(node->right->right);
				operations.push_back( Operation( OP_POP, REG_GR0 ) );	// 評価値の回収

				operations.push_back( Operation( lb2 ) );
			}
			else{
				int lb = label++;

				operations.push_back( Operation( OP_JZ, REG_GR0, lb ) );

				gen(node->right);
				operations.push_back( Operation( OP_POP, REG_GR0 ) );	// 評価値の回収

				operations.push_back( Operation( lb ) );
			}

			operations.push_back( Operation( OP_PUSH_I, 0 ) );	// if式としての評価値（0固定）

			break;

		case ND_WHILE:
		{
			int lb1 = label++;
			int lb2 = label++;

			operations.push_back( Operation( lb1 ) );

			gen(node->left);
			operations.push_back( Operation( OP_POP, REG_GR0 ) );
			operations.push_back( Operation( OP_JZ, REG_GR0, lb2 ) );

			gen(node->right);
			operations.push_back( Operation( OP_POP, REG_GR0 ) );	// 評価値の回収
			operations.push_back( Operation( OP_JMP, lb1 ) );

			operations.push_back( Operation( lb2 ) );
			operations.push_back( Operation( OP_PUSH_I, 0 ) );	// while式としての評価値（0固定）

			break;
		}

		case ND_BLOCK:
			gen(node->left);
			operations.push_back( Operation( OP_POP, REG_GR0 ) );

			gen(node->right);

			break;

		case ND_FUNC:
			curFunc = getFunc(node->name);

			operations.push_back( Operation( curFunc->label ) );
			gen(node->left);
			operations.push_back( Operation( OP_RET ) );

			break;

		case ND_ARG:
			argc++;
			gen(node->left);
			gen(node->right);

			break;

		case ND_CALL:
			argc = 0;
			gen(node->left);	// 引数の評価
			operations.push_back( Operation( OP_CALL, getFunc(node->name)->label, argc ) );

			break;

		case ND_RET:
			gen(node->left);
			operations.push_back( Operation( OP_RET ) );
			break;

		case ND_PUT:
			gen(node->left);
			operations.push_back( Operation( OP_PUT ) );
			break;

		default:
			break;
	}
};

vector<Operation> Generator::codegen(vector<Node*> &nodes)
{
	offset = 0;
	label = funcList.size();

	Function* mainFunc = getFunc("main");
	if(!mainFunc){
		cerr << "Error : function 'main' is not defined" << endl;
		exit(1);
	}

	// main関数の呼び出し
	operations.push_back( Operation( OP_CALL, mainFunc->label, 0 ) );
	operations.push_back( Operation( OP_EXIT ) );

	for(Node *node : nodes){
		gen(node);
	}

#ifdef CODEGEN_DEBUG
	cout << string(30, '-') << endl;
	for(Operation op : operations) op.print();
	cout << string(30, '-') << endl;
#endif

	return operations;
};
