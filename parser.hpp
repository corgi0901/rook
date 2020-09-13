#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <vector>
#include "container/node.hpp"
#include "container/token.hpp"
#include "type.hpp"

using namespace std;

class Parser
{
private:
	vector<Token>::iterator token;	// 現在注目しているトークン

	vector<Node*> program(void);
	Node* expr(void);
	Node* ifExpr(void);
	Node* whileExpr(void);
	Node* compare(void);
	Node* block(void);
	Node* num(void);
	Node* add(void);
	Node* mul(void);
	Node* unary(void);
	Node* primary(void);
	Node* ident(void);

	bool consume(string str);
	void expect(string str);

public:
	vector<Node*> parse(vector<Token>& tokens);
};

#endif // _PARSER_HPP_
