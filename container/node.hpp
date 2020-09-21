#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <string>

using namespace std;

// ノード関連の定義
typedef enum {
	ND_NUM,			// 数値
	ND_ADD,			// +
	ND_SUB,			// -
	ND_MUL,			// *
	ND_DIV,			// /
	ND_ASSIGN,		// =
	ND_IDENT,		// 識別子
	ND_EQ,			// ==
	ND_NEQ,			// !=
	ND_LESS,		// <
	ND_EQLESS,		// <=
	ND_IF,			// if
	ND_ELSE,		// else
	ND_WHILE,		// while
	ND_BLOCK,		// {}
	ND_FUNC,		// function
	ND_CALL,		// 関数呼び出し
	ND_ARG,			// 引数
	ND_RET,			// return
	ND_PUT,			// put
} NodeKind;

class Node
{
public:
	NodeKind kind;		// トークン種別
	Node *left = NULL;	// 左辺
	Node *right = NULL;	// 右辺
	int val;			// ND_NUMのときに使う
	string name;		// 変数名（ND_IDENTまたはND_FUNCのときに使う）

	Node(NodeKind kind);
	Node(NodeKind kind, Node* left, Node* right);
	Node(int val);
	Node(string name);
	Node(string name, Node* node);

	void print(void);
};

#endif // _NODE_HPP_
