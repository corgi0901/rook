#include <fstream>
#include <iostream>
#include <vector>
#include "container/function.hpp"
#include "generator.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"
#include "type.hpp"
#include "vm.hpp"

using namespace std;

vector<Function*> funcList;

int main(int argc, char* argv[])
{
	Tokenizer tokenizer;
	Parser parser;
	Generator generator;
	VM vm;

	if(argc < 2){
		return 0;
	}

	ifstream ifs(argv[1]);
	if (ifs.fail()) {
		cerr << "Error : Failed to open " << argv[1] << endl;
		return -1;
	}

	string input = string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

	// トークナイズ
	vector<Token> tokens = tokenizer.tokenize(input.c_str());
	
	// 構文解析
	vector<Node*> nodes = parser.parse(tokens);

	// コード生成
	vector<Operation> code = generator.codegen(nodes);

	// コード実行
	vm.run(code);

	return 0;
};
