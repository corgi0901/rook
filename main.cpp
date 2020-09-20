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

	// トークナイズ
	vector<Token> tokens = tokenizer.tokenize(argv[1]);
	
	// 構文解析
	vector<Node*> nodes = parser.parse(tokens);

	// コード生成
	vector<Operation> code = generator.codegen(nodes);

	// コード実行
	cout << vm.run(code) << endl;

	return 0;
};
