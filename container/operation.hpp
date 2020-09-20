#ifndef _OPERATION_HPP_
#define _OPERATION_HPP_

#include <string>
#include "../type.hpp"

using namespace std;

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
	OP_JMP,			// 無条件ジャンプ
	OP_JZ,			// ジャンプ（＝0のとき）
	OP_CALL,		// 関数呼び出し
	OP_RET,			// 関数からの戻り
	OP_EXIT,		// 終了命令
	OP_DUMMY,		// ダミー命令（ラベル用）
} OP_CODE;

class Operation
{
public:
	BYTE opcode;	// オペコード
	DWORD operand;	// オペランド
	DWORD operand2;	// 第2オペランド
	int label;		// ラベル番号

	Operation(BYTE opcode, DWORD operand);
	Operation(BYTE opcode, DWORD operand, DWORD operand2);
	Operation(int label);
	Operation(OP_CODE code);

	void print(void);
};

#endif // _OPERATION_HPP_
