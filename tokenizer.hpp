#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_

#include <vector>
#include "container/token.hpp"
#include "type.hpp"

using namespace std;

class Tokenizer
{
private:
	char* cursor;
	vector<Token> tokens;

	bool isAlnum(char c);
	bool isSymbol(void);
	bool isKeyword(void);
	bool isNumber(void);
	bool isIdentifier(void);
	bool isNewline(void);
	void skip(void);

public:
	vector<Token> tokenize(char* input);
};

#endif // _TOKENIZER_HPP_
