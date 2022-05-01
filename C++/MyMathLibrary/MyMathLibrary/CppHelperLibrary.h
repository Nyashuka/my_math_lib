#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <list>
#include <map>

namespace MathExpressions
{
	class MathExpression {
	public:
		std::list<std::string> _operators;
		std::list<std::string> _functions;
		std::map<std::string, double> _arguments;
		std::string _expression = "";	

		MathExpression();
		MathExpression(std::string expression);
		void SetArgument(std::string, double value);
		double Calculate();
		double Calculate(std::string expression);
	private:
		int GetPriority(std::string operation);
		std::vector<std::string> ExpressionToReversePolishNotation(std::string expression);
		double Solve(double firstOperand, double secondOperand, std::string operation);
		double Solve(double number, std::string function);
		bool IsNegative(std::string str);
		bool IsNumber(std::string str);
		bool IsFunction(std::string str);
		bool IsArgument(std::string str);
		bool IsOperation(std::string str);
		void ReplaceArgumentValue(std::vector<std::string> rpnString);
		double CalculateRPN(std::vector<std::string> rpnString);
	};
}

namespace JustHelper
{
	std::vector<std::string> SplitString(std::string str, char symbolForSplit = ' ');	
}
