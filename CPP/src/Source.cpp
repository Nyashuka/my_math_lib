#include "CppHelperLibrary.h"
#include <string> 


int main()
{
	using std::cout;
	using std::cin;
	using std::endl;
	using std::string;
	using std::vector;
	using std::getline;

	MathExpressions::MathExpression calculator;
	while(1)
	{
		cout << "Enter your expression or tupe q for to quit: ";
		std::string expression = "";
		getline(cin, expression);

		if(expression == "q")
			break;

		// calculator.ChangeExpression(expression);

		// calculator.SetArgument("x", 2);

		// cout << calculator.Calculate() << endl;

		// cin;
	}

	return 0;
}