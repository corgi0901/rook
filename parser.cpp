#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "parser.hpp"
#include "rook.hpp"

using namespace std;

vector<Node*> Parser::program(void)
{
	vector<Node*> nodes;

	nodes.push_back(add());

	while(consume(",") || consume("\n")){
		nodes.push_back(add());
	}

	return nodes;
};

Node* Parser::num(void)
{
	if(TK_NUM != token->kind){
		cerr << "Error : expect number" << endl;
		exit(1);
	}

	Node* node = new Node();
	node->kind = ND_NUM;
	node->val = atoi(token->str);
	token++;
	return node;
};

Node* Parser::add(void)
{
	Node* node = mul();

	while(1){
		if(consume("+")){
			node = new Node{ ND_ADD, node, mul() };
		}
		else if(consume("-")){
			node = new Node{ ND_SUB, node, mul() };
		}
		else{
			return node;
		}
	}
};

Node* Parser::mul(void)
{
	Node* node = unary();

	while(1){
		if(consume("*")){
			node = new Node{ ND_MUL, node, unary() };
		}
		else if(consume("/")){
			node = new Node{ ND_DIV, node, unary() };
		}
		else{
			return node;
		}
	}
};

Node* Parser::unary(void)
{
	if(consume("+")){
		return primary();
	}
	else if(consume("-")){
		Node* zero = new Node();
		zero->kind = ND_NUM;
		zero->val = 0;
		Node* node = new Node{ ND_SUB, zero, primary() };
		return node;
	}
	else{
		return primary();
	}
};

Node* Parser::primary(void)
{
	if(consume("(")){
		Node* addNode = add();
		expect(")");
		return addNode;
	}
	else{
		return num();
	}
};

bool Parser::consume(const char* str)
{
	if(TK_EOF == token->kind) return false;

	if(strncmp(str, token->str, token->len) == 0){
		token++;
		return true;
	}

	return false;
};

void Parser::expect(const char* str)
{
	if(TK_EOF == token->kind || strncmp(str, token->str, token->len)){
		cerr << "Error : expect \"" << str << "\"" << endl;
		exit(1);
	}
	else{
		token++;
	}
};

vector<Node*> Parser::parse(vector<Token>& tokens)
{
	token = tokens.begin();
	return program();
};
