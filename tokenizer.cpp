#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "tokenizer.hpp"
#include "type.hpp"

using namespace std;

//#define TOKENIZE_DEBUG

static const char* symbols[] = {
	"+", "-", "*", "/",
	"(", ")", "{", "}", ",",
	"==", "=", "!=", "<=", "<", ">=", ">",
};

static const char* keywords[] = {
	"if", "else", "while", "func", "return"
};

bool Tokenizer::isAlnum(char c)
{
	if(isalnum(c) || '_' == c){
		return true;
	}
	else{
		return false;
	}
};

bool Tokenizer::isSymbol(void)
{
	for(const char* symbol : symbols){
		int len = strlen(symbol);
		if(strncmp(cursor, symbol, len) == 0){
			Token token(TK_RESERVED, cursor, len);
			tokens.push_back(token);
			cursor += len;
			return true;
		}
	}
	return false;
};

bool Tokenizer::isKeyword(void)
{
	for(const char* keyword : keywords){
		int len = strlen(keyword);
		if(strncmp(cursor, keyword, len) == 0 && !isAlnum(*(cursor+len))){
			Token token(TK_RESERVED, cursor, len);
			tokens.push_back(token);
			cursor += len;
			return true;
		}
	}
	return false;
};

bool Tokenizer::isNumber(void)
{
	char* p = cursor;
	int len = 0;
	for(; isdigit(*cursor); cursor++) len++;

	if(len > 0){
		Token token(TK_NUM, p, len);
		tokens.push_back(token);
		return true;
	}
	
	return false;
};

bool Tokenizer::isIdentifier(void)
{
	char* p = cursor;
	int len = 0;
	for(; isAlnum(*cursor); cursor++) len++;

	if(len > 0){
		Token token(TK_IDENT, p, len);
		tokens.push_back(token);
		return true;
	}

	return false;
};

bool Tokenizer::isNewline(void)
{
	if(*cursor == '\n'){
		// 先頭または連続した改行は受け付けない
		if(tokens.size() != 0 && tokens.back().str != "\n"){
			Token token(TK_RESERVED, cursor, 1);
			tokens.push_back(token);
		}
		cursor++;
		return true;
	}
	return false;
};

void Tokenizer::skip(void)
{
	while(*cursor != '\n' && isspace(*cursor)){
		cursor++;
	}
};

vector<Token> Tokenizer::tokenize(char* input)
{
	cursor = input;
	tokens.clear();

	while(*cursor){

		skip();

		if(isSymbol()){
			/* Do Nothing */
		}
		else if(isKeyword()){
			/* Do Nothing */
		}
		else if(isNumber()){
			/* Do Nothing */
		}
		else if(isIdentifier()){
			/* Do Nothing */
		}
		else if(isNewline()){
			/* Do Nothing */
		}
		else{
			cerr << "Error : invalid character : " << *cursor << endl;
			exit(1);
		}
	}

	// 末尾が改行だったら削除
	if(tokens.back().str == "\n"){
		tokens.pop_back();
	}

	tokens.push_back( Token(TK_EOF, cursor, 0) );

#ifdef TOKENIZE_DEBUG
	cout << string(30, '-') << endl;
	for(Token token : tokens) token.print();
	cout << string(30, '-') << endl;
#endif

	return tokens;
};
