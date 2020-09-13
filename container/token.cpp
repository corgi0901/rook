#include <iostream>
#include <map>
#include <string>
#include "token.hpp"

using namespace std;

static map<TokenKind, string> printTbl = {
	{ TK_NUM,		"NUM"	},
	{ TK_RESERVED,	"RESV"	},
	{ TK_IDENT,		"IDENT"	},
	{ TK_EOF,		"EOF"	},
};

Token::Token(TokenKind kind, const char* p, int len)
{
	this->kind = kind;
	str = string(p, len);
};

void Token::print(void)
{
	cout << printTbl[kind] << "\t" << "\"" << str <<  "\"" << endl;
};
