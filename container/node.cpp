#include <iostream>
#include <map>
#include <string>
#include "node.hpp"

using namespace std;

static map<NodeKind, string> printTbl = {
	{ ND_ADD,		"+"		},
	{ ND_SUB,		"-"		},
	{ ND_MUL,		"*"		},
	{ ND_DIV,		"/"		},
	{ ND_ASSIGN,	"="		},
	{ ND_EQ,		"=="	},
	{ ND_NEQ,		"!="	},
	{ ND_LESS,		"<"		},
	{ ND_EQLESS,	"<="	},
	{ ND_IF,		"if"	},
	{ ND_ELSE,		"else"	},
	{ ND_WHILE,		"while"	},
	{ ND_BLOCK,		"BLK"	},
};

Node::Node(NodeKind kind, Node* left, Node* right)
{
	this->kind = kind;
	this->left = left;
	this->right = right;
};

Node::Node(int val){
	kind = ND_NUM;
	this->val = val;
};

Node::Node(string name){
	kind = ND_IDENT;
	this->name = name;
};

void Node::print(void)
{
	switch(this->kind){
		case ND_NUM:
			cout << val;
			return;
		case ND_IDENT:
			cout << name;
			return;
		default:
			break;
	};

	cout << "( " << printTbl[kind] << " ";
	left->print();
	cout << " ";
	right->print();
	cout << " )";
};
