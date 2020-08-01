#include <cstdlib>
#include <vector>
#include "parser.hpp"
#include "rook.hpp"

using namespace std;

Node* Parser::program(void)
{
	return num();	
};

Node* Parser::num(void)
{
	Node* node = new Node();
	node->kind = ND_NUM;
	node->val = atoi(token->str);
	token++;
	return node;
};

Node* Parser::parse(vector<Token>& tokens)
{
	token = tokens.begin();
	return program();
};
