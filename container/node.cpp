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
	{ ND_FUNC,		"FUNC"	},
	{ ND_CALL,		"CALL"	},
	{ ND_ARG,		"ARG"	},
	{ ND_RET,		"RET"	},
	{ ND_PUT,		"PUT"	},
};

Node::Node(NodeKind kind)
{
	this->kind = kind;
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

Node::Node(string name, Node* node)
{
	kind = ND_FUNC;
	this->name = name;
	this->left = node;
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

	if(kind == ND_CALL) cout << name << " ";

	if(left){
		left->print();
	}
	else{
		cout << "_";
	}

	cout << " ";

	if(right){
		right->print();
	}
	else{
		cout << "_";
	}

	cout << " )";
};
