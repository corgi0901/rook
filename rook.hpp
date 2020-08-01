#ifndef ROOK_HPP_
#define ROOK_HPP_

// 型定義
#define BYTE	unsigned char
#define DWORD	int

// トークン関連の定義
typedef enum {
	TK_NUM,			// 数値
	TK_OP,			// 演算子
	TK_EOF,			// 終端
} TokenKind;

typedef struct {
	TokenKind kind;	// トークン種別
	char *str;		// トークン文字列
	int len;		// トークン長
} Token;


// ノード関連の定義
typedef enum {
	ND_NUM,			// 数値
	ND_ADD,			// +
	ND_SUB,			// -
} NodeKind;

typedef struct Node Node;

struct Node {
	NodeKind kind;	// トークン種別
	Node *left;		// 左辺
	Node *right;	// 右辺
	int val;		// ND_NUMのときに使う
};


// 命令関連の定義
typedef enum {
	OP_PUSH,		// Push
	OP_POP,			// Pop
	OP_ADD,			// 加算
	OP_SUB,			// 減算
} OP_CODE;

typedef struct {
	BYTE opcode;	// オペコード
	DWORD operand;	// オペランド
	DWORD operand2;	// 第2オペランド
} Operation;


// レジスタ関連定義
typedef enum {
	REG_GR0 = 0,
	REG_GR1,
	REG_NUM,		// レジスタ数
} REG_NAME;

#endif // ROOK_HPP_
