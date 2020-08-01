#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
#include "rook.hpp"

using namespace std;

class Parser
{
private:
	vector<Token>::iterator token;	// 現在注目しているトークン

	Node* program(void);
	Node* num(void);
	Node* add(void);

	bool consume(const char* str);

public:
	Node* parse(vector<Token>& tokens);
};

#endif // PARSER_HPP_
