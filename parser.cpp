#include <cstdlib>
#include <cstring>
#include <vector>
#include "parser.hpp"
#include "rook.hpp"

using namespace std;

Node* Parser::program(void)
{
	return add();
};

Node* Parser::num(void)
{
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
	Node* node = num();

	while(1){
		if(consume("*")){
			node = new Node{ ND_MUL, node, num() };
		}
		else if(consume("/")){
			node = new Node{ ND_DIV, node, num() };
		}
		else{
			return node;
		}
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

Node* Parser::parse(vector<Token>& tokens)
{
	token = tokens.begin();
	return program();
};
