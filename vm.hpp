#ifndef _VM_HPP_
#define _VM_HPP_

#include <vector>
#include "container/operation.hpp"
#include "type.hpp"

using namespace std;

// レジスタ関連定義
typedef enum {
	REG_GR0,
	REG_GR1,
	REG_RAX,
	REG_NUM,	// レジスタ数
} REG_NAME;

class VM
{
private:
	DWORD* stack;	// スタック
	DWORD* sp;		// スタックポインタ
	DWORD* bp;		// ベースポインタ

	DWORD* reg;		// レジスタ

	void push(DWORD val);
	DWORD pop(void);

	void print(void);

public:
	VM(void);
	DWORD run(vector<Operation>& code);
};

#endif // _VM_HPP_
