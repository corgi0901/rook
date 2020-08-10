#ifndef ROOK_HPP_
#define ROOK_HPP_

// 型定義
#define BYTE	unsigned char
#define DWORD	int

// トークン関連の定義
typedef enum {
	TK_NUM,			// 数値
	TK_RESERVED,	// 記号
	TK_IDENT,		// 識別子
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
	ND_MUL,			// *
	ND_DIV,			// /
	ND_ASSIGN,		// =
	ND_IDENT,		// 識別子
	ND_EQ,			// ==
	ND_NEQ,			// !=
	ND_LESS,		// <
	ND_EQLESS,		// <=
} NodeKind;

typedef struct Node Node;

struct Node {
	NodeKind kind;	// トークン種別
	Node *left;		// 左辺
	Node *right;	// 右辺
	int val;		// ND_NUMのときに使う
	char* name;		// 変数名（ND_IDENTのときに使う）
	int len;		// 名前長（ND_IDENTのときに使う）
};


// 命令関連の定義
typedef enum {
	OP_PUSH,		// Push（レジスタ値）
	OP_PUSH_I,		// Push（即値）
	OP_POP,			// Pop
	OP_ADD,			// 加算
	OP_SUB,			// 減算
	OP_MUL,			// 乗算
	OP_DIV,			// 除算
	OP_EQ,			// ==
	OP_NEQ,			// !=
	OP_LESS,		// <
	OP_EQLESS,		// <=
	OP_STORE,		// レジスタ→メモリへの書き込み
	OP_LOAD,		// メモリ→レジスタへの読み込み
} OP_CODE;

typedef struct {
	BYTE opcode;	// オペコード
	DWORD operand;	// オペランド
	DWORD operand2;	// 第2オペランド
} Operation;


// 変数定義
typedef struct {
	char* name;		// 変数名
	int len;		// 名前長
	int	offset;		// データ格納先のオフセット
} Variable;

// レジスタ関連定義
typedef enum {
	REG_GR0 = 0,
	REG_GR1,
	REG_NUM,		// レジスタ数
} REG_NAME;

#endif // ROOK_HPP_
