#include <cstring>
#include <iostream>
#include <vector>
#include "rook.hpp"
#include "vm.hpp"

using namespace std;

VM::VM()
{
	memset(stack, 0, sizeof(stack));
	bp = stack;
	sp = &stack[16];
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
				push(reg[op->operand]);
				break;
			}
			case OP_PUSH_I:
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
			case OP_EQ:
			{
				push(reg[op->operand] == reg[op->operand2]);
				break;
			}
			case OP_NEQ:
			{
				push(reg[op->operand] != reg[op->operand2]);
				break;
			}
			case OP_LESS:
			{
				push(reg[op->operand] < reg[op->operand2]);
				break;
			}
			case OP_EQLESS:
			{
				push(reg[op->operand] <= reg[op->operand2]);
				break;
			}
			case OP_STORE:
			{
				bp[reg[op->operand]] = reg[op->operand2];
				break;
			}
			case OP_LOAD:
			{
				reg[op->operand] = bp[reg[op->operand2]];
				break;
			}
			default:
				break;
		}
		op++;
	}

	// GR0レジスタの値を実行結果とする
	return reg[REG_GR0];
};
