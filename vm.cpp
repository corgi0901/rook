#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include "container/operation.hpp"
#include "type.hpp"
#include "vm.hpp"

//#define VM_DEBUG

using namespace std;

// サイズ定義
#define STACK_SIZE	512	// スタックの深さ
#define LVAR_SIZE 10 // 変数領域のサイズ

VM::VM()
{
	stack = new DWORD[STACK_SIZE];
	reg = new DWORD[REG_NUM];
	bp = stack;
	sp = bp + LVAR_SIZE;
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
	vector<Operation>::iterator op;
	map<int, vector<Operation>::iterator> labelMap;

	for(op = code.begin(); op != code.end(); op++){
		if(OP_DUMMY == op->opcode){
			labelMap[op->label] = op;
		}
	}

	op = code.begin();

	while(op->opcode != OP_EXIT){

#ifdef VM_DEBUG
		op->print();
#endif

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
			case OP_JMP:
			{
				op = labelMap[op->operand];
				break;
			}
			case OP_JZ:
			{
				if(0 == reg[op->operand]){
					op = labelMap[op->operand2];
				}
				break;
			}
			case OP_CALL:
			{
				int rbp = bp - stack;

				bp = sp - op->operand2 + 1;
				sp = bp + LVAR_SIZE;

				push(rbp);
				push(op - code.begin());

				op = labelMap[op->operand];

				break;
			}
			case OP_RET:
			{
				reg[REG_RAX] = pop();
				int rop = pop();
				int rbp = pop();

				sp = bp - 1;
				bp = stack + rbp;
				op = code.begin() + rop;

				push(reg[REG_RAX]);
				break;
			}
			default:
				break;
		}

#ifdef VM_DEBUG
		this->print();
		cout << endl;
#endif

		op++;
	}

	// RAXレジスタの値を実行結果とする
	return reg[REG_RAX];
};

void VM::print(void)
{
	cout << "STK | ";
	for(DWORD *p = stack; p <= sp; p++){
		if(p == bp){
			cout << "\033[32m" << *p << "\033[m" << ", ";
		}
		else{
			cout << *p << ", ";
		}
	};
	cout << endl;

	cout << "REG | ";
	for(int i = 0; i < REG_NUM; i++){
		cout << reg[i] << ", ";
	};
	cout << endl;
};
