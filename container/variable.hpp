#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_

#include <string>

using namespace std;

class Variable
{
public:
	string name;	// 変数名
	int	offset;		// データ格納先のオフセット

	Variable(string name, int offset);

	void print(void);
};

#endif // _VARIABLE_HPP_
