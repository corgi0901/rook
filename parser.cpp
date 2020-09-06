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

	nodes.push_back(expr());

	while(consume(",") || consume("\n")){
		nodes.push_back(expr());
	}

	return nodes;
};

Node* Parser::expr(void)
{
	if(TK_IDENT == token->kind && strncmp((token+1)->str, "=", 1) == 0 && (token+1)->len == 1){
		Node* ident = new Node();
		ident->kind = ND_IDENT;
		ident->name = token->str;
		ident->len = token->len;
		token++;
		expect("=");
		Node* node = new Node{ ND_ASSIGN, ident, compare() };
		return node;
	}
	else if(TK_RESERVED == token->kind && strncmp(token->str, "if", 2) == 0){
		return ifExpr();
	}
	else if(TK_RESERVED == token->kind && strncmp(token->str, "while", 5) == 0){
		return whileExpr();
	}
	else if(TK_RESERVED == token->kind && strncmp(token->str, "{", 1) == 0){
		return block();
	}
	else{
		return compare();
	}
};

Node* Parser::ifExpr(void)
{
	Node* node;

	expect("if");
	expect("(");
	Node* cond = compare();
	expect(")");
	consume("\n");

	Node *expr1 = expr();

	if(strncmp(token->str, "\n", 1) == 0 && strncmp((token+1)->str, "else", 4) == 0){
		consume("\n");
	}

	if(consume("else")){
		consume("\n");
		Node* expr2 = expr();
		Node* elseNode = new Node{ ND_ELSE, expr1, expr2 };
		node = new Node{ ND_IF, cond, elseNode };
	}
	else{
		node = new Node{ ND_IF, cond, expr1 };
	}

	return node;
};

Node* Parser::whileExpr(void)
{
	expect("while");
	expect("(");
	Node* cond = compare();
	expect(")");
	consume("\n");
	Node* node = new Node{ ND_WHILE, cond, expr() };
	return node;
};

Node* Parser::block(void)
{
	expect("{");
	consume("\n");

	Node* node = expr();

	while(1){
		if(consume(",")){
			node = new Node{ ND_BLOCK, node, expr() };
		}
		else if(consume("\n")){
			if(consume("}")) return node;
			node = new Node{ ND_BLOCK, node, expr() };
		}
		else{
			expect("}");
			return node;
		}
	}
};

Node* Parser::compare(void)
{
	Node* addNode = add();
	Node* node;
	if(consume("==")){
		node = new Node{ ND_EQ, addNode, add()};
	}
	else if(consume("!=")){
		node = new Node{ ND_NEQ, addNode, add()};
	}
	else if(consume("<")){
		node = new Node{ ND_LESS, addNode, add()};
	}
	else if(consume("<=")){
		node = new Node{ ND_EQLESS, addNode, add()};
	}
	else if(consume(">")){
		node = new Node{ ND_LESS, add(), addNode}; // 右左辺を入れ替え
	}
	else if(consume(">=")){
		node = new Node{ ND_EQLESS, add(), addNode}; // 右左辺を入れ替え
	}
	else{
		return addNode;
	}

	return node;
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
		Node* node = compare();
		expect(")");
		return node;
	}
	else if(TK_IDENT == token->kind){
		return ident();
	}
	else{
		return num();
	}
};

Node* Parser::ident(void)
{
	Node* node = new Node();
	node->kind = ND_IDENT;
	node->name = token->str;
	node->len = token->len;
	token++;
	return node;
};

bool Parser::consume(const char* str)
{
	if(TK_EOF == token->kind) return false;

	if(strlen(str) == token->len && strncmp(str, token->str, token->len) == 0){
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
	vector<Node*> nodes = program();

	if(TK_EOF != token->kind){
		cerr << "Error : Failed to parse" << endl;
		exit(1);
	}

	return nodes;
};
