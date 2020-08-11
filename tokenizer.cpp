#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "rook.hpp"
#include "tokenizer.hpp"

using namespace std;

bool Tokenizer::isAlnum(char c)
{
	if(isalnum(c) || '_' == c){
		return true;
	}
	else{
		return false;
	}
};

vector<Token> Tokenizer::tokenize(char* input)
{
	vector<Token> tokens;

	while(*input){
		if(strncmp(input, "\n", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(isspace(*input)){
			input++;
		}
		else if(strncmp(input, "+", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, "-", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, "*", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, "/", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, "(", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, ")", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, ",", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, "==", 2) == 0){
			Token token = { TK_RESERVED, input, 2 };
			tokens.push_back(token);
			input += 2;
		}
		else if(strncmp(input, "!=", 2) == 0){
			Token token = { TK_RESERVED, input, 2 };
			tokens.push_back(token);
			input += 2;
		}
		else if(strncmp(input, "<=", 2) == 0){
			Token token = { TK_RESERVED, input, 2 };
			tokens.push_back(token);
			input += 2;
		}
		else if(strncmp(input, "<", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, ">=", 2) == 0){
			Token token = { TK_RESERVED, input, 2 };
			tokens.push_back(token);
			input += 2;
		}
		else if(strncmp(input, ">", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(strncmp(input, "=", 1) == 0){
			Token token = { TK_RESERVED, input, 1 };
			tokens.push_back(token);
			input++;
		}
		else if(isdigit(*input)){
			Token token = { TK_NUM, input, 0 };
			for(; isdigit(*input); input++) token.len++;
			tokens.push_back(token);
		}
		else if(isAlnum(*input)){
			Token token = { TK_IDENT, input, 0 };
			for(; isAlnum(*input); input++) token.len++;
			tokens.push_back(token);
		}
		else{
			cerr << "Invalid character : " << *input << endl;
			exit(1);
		}
	}

	tokens.push_back( Token{ TK_EOF, input, 0 } );

	return tokens;
};
