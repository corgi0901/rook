#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
#include "rook.hpp"

using namespace std;

class Parser
{
private:
	vector<Token>::iterator token;	// 現在注目しているトークン

	vector<Node*> program(void);
	Node* expr(void);
	Node* num(void);
	Node* add(void);
	Node* mul(void);
	Node* unary(void);
	Node* primary(void);

	bool consume(const char* str);
	void expect(const char* str);

public:
	vector<Node*> parse(vector<Token>& tokens);
};

#endif // PARSER_HPP_
