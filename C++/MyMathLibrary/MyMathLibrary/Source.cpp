#include "CppHelperLibrary.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
	

	MathExpressions::MathExpression expression("x*sin(1)+3^(1+1)");
	expression.SetArgument("x", 2);

	cout << expression.Calculate() << endl;

	return 0;
}