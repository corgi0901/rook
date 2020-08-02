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
			case OP_POP:
			{
				reg[op->operand] = pop();
				break;
			}
			case OP_ADD:
			{
				push(reg[op->operand] + reg[op->operand2]);
				break;
			}
			case OP_SUB:
			{
				push(reg[op->operand] - reg[op->operand2]);
				break;
			}
			case OP_MUL:
			{
				push(reg[op->operand] * reg[op->operand2]);
				break;
			}
			case OP_DIV:
			{
				push(reg[op->operand] / reg[op->operand2]);
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
