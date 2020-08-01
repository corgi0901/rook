#include <iostream>
#include <vector>
#include "generator.hpp"
#include "parser.hpp"
#include "rook.hpp"
#include "tokenizer.hpp"
#include "vm.hpp"

using namespace std;

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
	Node* node = parser.parse(tokens);

	// コード生成
	vector<Operation> code = generator.codegen(node);

	// コード実行
	cout << vm.run(code) << endl;

	return 0;
};
