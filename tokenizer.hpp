#ifndef TOKENIZER_HPP_
#define TOKENIZER_HPP_

#include <vector>
#include "rook.hpp"

using namespace std;

class Tokenizer
{
private:
	bool isAlnum(char c);

public:
	vector<Token> tokenize(char* input);
};

#endif // TOKENIZER_HPP_
