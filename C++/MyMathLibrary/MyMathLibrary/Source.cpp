#include <iostream>
#include "CppHelperLibrary.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

int main()
{
	vector<string> arr = JustHelper::SplitString("lol yes hello");
	
	for (size_t i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << std::endl;
	}
	
	MathExpressions::MathExpression expession;


	return 0;
}