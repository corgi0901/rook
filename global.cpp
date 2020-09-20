#include <string>
#include <vector>
#include "global.hpp"

using namespace std;

Function* getFunc(string name)
{
	for(Function* fn : funcList){
		if(name == fn->name){
			return fn;
		}
	}
	return NULL;
};
