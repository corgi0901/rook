#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "rook.hpp"
#include "tokenizer.hpp"

using namespace std;

vector<Token> Tokenizer::tokenize(char* input)
{
	vector<Token> tokens;

	while(*input){
		if(isdigit(*input)){
			Token token = { TK_NUM, input, 0 };
			for(; isdigit(*input); input++) token.len++;
			tokens.push_back(token);
		}
		else{
			cerr << "Invalid character : " << *input << endl;
			exit(1);
		}
	}

	tokens.push_back( Token{ TK_EOF, NULL, 0 } );

	return tokens;
};
