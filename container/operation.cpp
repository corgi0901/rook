#include <iostream>
#include <map>
#include "operation.hpp"
#include "../vm.hpp"

using namespace std;

static map<DWORD, string> regMap = {
	{ REG_GR0, "GR0" },
	{ REG_GR1, "GR1" },
	{ REG_RAX, "RAX" },
};

Operation::Operation(BYTE opcode, DWORD operand)
{
	this->opcode = opcode;
	this->operand = operand;
};

Operation::Operation(BYTE opcode, DWORD operand, DWORD operand2)
{
	this->opcode = opcode;
	this->operand = operand;
	this->operand2 = operand2;
};

Operation::Operation(int label)
{
	opcode = OP_DUMMY;
	this->label = label;
};

Operation::Operation(OP_CODE code)
{
	opcode = code;
};

void Operation::print(void)
{
	switch(this->opcode)
	{
		case OP_PUSH:
			cout <<  "PUSH\t" << regMap[operand] << endl;
			break;
		case OP_PUSH_I:
			cout <<  "PUSH_I\t" << operand << endl;
			break;
		case OP_POP:
			cout <<  "POP\t" << regMap[operand] << endl;
			break;
		case OP_ADD:
			cout <<  "ADD\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_SUB:
			cout <<  "SUB\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_MUL:
			cout <<  "MUL\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_DIV:
			cout <<  "DIV\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_EQ:
			cout <<  "EQ\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_NEQ:
			cout <<  "NEQ\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_LESS:
			cout <<  "LESS\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_EQLESS:
			cout <<  "EQLESS\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_STORE:
			cout <<  "STORE\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_LOAD:
			cout <<  "LOAD\t" << regMap[operand] << "\t" << regMap[operand2] << endl;
			break;
		case OP_JMP:
			cout <<  "JMP\t" << operand << endl;
			break;
		case OP_JZ:
			cout <<  "JZ\t" << regMap[operand] << "\t" << operand2 << endl;
			break;
		case OP_CALL:
			cout <<  "CALL\t" << operand << "\t" << operand2 << endl;
			break;
		case OP_RET:
			cout <<  "RET\t" << endl;
			break;
		case OP_EXIT:
			cout <<  "EXIT\t" << endl;
			break;
		case OP_DUMMY:
			cout <<  "LABEL:" << label << endl;
			break;
		default:
			cout << "Unknown Operation" << endl;
			break;
	}
};
