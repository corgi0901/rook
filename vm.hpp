#ifndef VM_HPP_
#define VM_HPP_

#include <vector>
#include "rook.hpp"

using namespace std;

// サイズ定義
#define STACK_SIZE	512	// スタックの深さ

class VM
{
private:
	DWORD stack[STACK_SIZE];	// スタック
	DWORD* sp;					// スタックポインタ

	DWORD reg[REG_NUM];			// レジスタ

	void push(DWORD val);
	DWORD pop(void);

public:
	VM();
	DWORD run(vector<Operation>& code);
};

#endif // VM_HPP_
