#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "container/function.hpp"
#include "container/node.hpp"
#include "container/token.hpp"
#include "global.hpp"
#include "parser.hpp"
#include "type.hpp"

//#define PARSE_DEBUG

using namespace std;

vector<Node*> Parser::program(void)
{
	vector<Node*> nodes;

	nodes.push_back(func());

	while(consume(",") || consume("\n")){
		nodes.push_back(func());
	}

	return nodes;
};

Node* Parser::expr(void)
{
	if(TK_IDENT == token[0].kind && token[1].str == "="){
		Node* _ident = ident();
		expect("=");
		Node* node = new Node(ND_ASSIGN, _ident, compare());
		return node;
	}
	else if(token->str == "if"){
		return ifExpr();
	}
	else if(token->str == "while"){
		return whileExpr();
	}
	else if(token->str == "{"){
		return block();
	}
	else if(token->str == "return"){
		return ret();
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

	if(token[0].str == "\n" && token[1].str == "else"){
		consume("\n");
	}

	if(consume("else")){
		consume("\n");
		Node* expr2 = expr();
		Node* elseNode = new Node(ND_ELSE, expr1, expr2);
		node = new Node(ND_IF, cond, elseNode);
	}
	else{
		node = new Node(ND_IF, cond, expr1);
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
	Node* node = new Node(ND_WHILE, cond, expr());
	return node;
};

Node* Parser::func(void)
{
	expect("func");

	if(token->kind != TK_IDENT){
		cerr << "Error : expect identifier" << endl;
		exit(1);
	}

	string name = token->str;
	token++;

	// 関数リストに登録
	Function* fn = new Function(name);
	funcList.push_back(fn);

	expect("(");

	// 引数の処理
	if(token->kind == TK_IDENT){
		ident();
		while(consume(",")) ident();
	}

	expect(")");

	consume("\n");

	Node* node = new Node(name, block());

	return node;
};

Node* Parser::block(void)
{
	expect("{");
	consume("\n");

	Node* node = expr();

	while(1){
		if(consume(",")){
			node = new Node(ND_BLOCK, node, expr());
		}
		else if(consume("\n")){
			if(consume("}")) return node;
			node = new Node(ND_BLOCK, node, expr());
		}
		else{
			expect("}");
			return node;
		}
	}
};

Node* Parser::ret(void)
{
	expect("return");
	Node* node = new Node(ND_RET, expr(), NULL);
	return node;
};

Node* Parser::compare(void)
{
	Node* addNode = add();
	Node* node;
	if(consume("==")){
		node = new Node(ND_EQ, addNode, add());
	}
	else if(consume("!=")){
		node = new Node(ND_NEQ, addNode, add());
	}
	else if(consume("<")){
		node = new Node(ND_LESS, addNode, add());
	}
	else if(consume("<=")){
		node = new Node(ND_EQLESS, addNode, add());
	}
	else if(consume(">")){
		node = new Node(ND_LESS, add(), addNode); // 右左辺を入れ替え
	}
	else if(consume(">=")){
		node = new Node(ND_EQLESS, add(), addNode); // 右左辺を入れ替え
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

	Node* node = new Node(stoi(token->str));
	token++;
	return node;
};

Node* Parser::add(void)
{
	Node* node = mul();

	while(1){
		if(consume("+")){
			node = new Node(ND_ADD, node, mul());
		}
		else if(consume("-")){
			node = new Node(ND_SUB, node, mul());
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
			node = new Node(ND_MUL, node, unary());
		}
		else if(consume("/")){
			node = new Node(ND_DIV, node, unary());
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
		Node* zero = new Node(0);
		Node* node = new Node(ND_SUB, zero, primary());
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
	else if(TK_IDENT == token->kind && (token+1)->str == "("){
		return call();
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
	Node* node = new Node(token->str);
	token++;

	// 変数登録
	Function* curFunc = funcList.back();
	if(false == curFunc->hasVar(node->name)){
		curFunc->addVar(node->name);
	}

	return node;
};

Node* Parser::call(void)
{
	Node* node = new Node(ND_CALL);
	node->name = token->str;
	token++;
	expect("(");

	if(false == consume(")")){
		node->left = arg();
		expect(")");
	}

	return node;
};

Node* Parser::arg(void)
{
	Node* node;
	Node* left = expr();

	if(consume(",")){
		node = new Node(ND_ARG, left, arg());
	}
	else{
		node = new Node(ND_ARG, left, NULL);
	}

	return node;
};

bool Parser::consume(string str)
{
	if(TK_EOF == token->kind) return false;

	if(str == token->str){
		token++;
		return true;
	}

	return false;
};

void Parser::expect(string str)
{
	if(TK_EOF == token->kind || str != token->str){
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

#ifdef PARSE_DEBUG
	cout << string(30, '-') << endl;
	for(Node* node : nodes){
		node->print();
		cout << endl;
	}
	for(Function* func : funcList){
		func->print();
	}
	cout << string(30, '-') << endl;
#endif

	return nodes;
};
