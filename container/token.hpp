#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>

using namespace std;

// トークン関連の定義
typedef enum {
	TK_NUM,			// 数値
	TK_RESERVED,	// 記号
	TK_IDENT,		// 識別子
	TK_EOF,			// 終端
} TokenKind;

class Token
{
public:
	TokenKind kind;
	string str;

	Token(TokenKind kind, const char* p, int len);
	void print(void);
};

#endif // _TOKEN_HPP_