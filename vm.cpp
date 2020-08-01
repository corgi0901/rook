#include <iostream>
#include <vector>
#include "rook.hpp"
#include "vm.hpp"

using namespace std;

VM::VM()
{
	sp = stack;
};

void VM::push(DWORD val)
{
	*(++sp) = val;
};

DWORD VM::pop(void)
{
	return *(sp--);
};

DWORD VM::run(vector<Operation>& code)
{
	vector<Operation>::iterator op = code.begin();

	while(op != code.end()){
		switch(op->opcode){
			case OP_PUSH:
			{
				push(op->operand);
				break;
			}
			default:
				break;
		}
		op++;
	}

	// スタックトップの値を実行結果とする
	return pop();
};
