#ifndef _GLOBAL_HPP_
#define _GLOBAL_HPP_

#include <vector>
#include "container/function.hpp"

using namespace std;

extern vector<Function*> funcList;

Function* getFunc(string name);

#endif // _GLOBAL_HPP_
