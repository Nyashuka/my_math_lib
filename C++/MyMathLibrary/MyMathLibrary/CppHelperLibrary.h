#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <math.h>
#include <vector>
#include <list>
#include <map>
#include <set>

namespace MathExpressions
{
	class MathExpression {
	public:
		MathExpression();
		MathExpression(std::string expression);
		~MathExpression();
		void SetArgument(std::string argumentName, double value);
		double Calculate();
		double Calculate(std::string expression);
	private:
		std::set<std::string> _operators = { "+", "-", "/", "*", "^" };
		std::set<std::string> _functions = { "sin", "cos", "tan", "ctg", "ln", "log", "lg", "log10" };
		std::map<std::string, double> _arguments;
		std::string _expression = "";
		bool _expressionIsInitialized = false;

		int GetPriority(std::string operation);
		std::vector<std::string> ExpressionToReversePolishNotation(std::string expression);
		double Solve(double firstOperand, double secondOperand, std::string operation);
		double Solve(double number, std::string function);
		bool IsNegative(std::string str);
		bool IsNumber(std::string str);
		bool IsFunction(std::string str);
		bool IsArgument(std::string str);
		bool IsOperation(std::string str);
		std::vector<std::string> ReplaceArgumentValue(std::vector<std::string> rpnString);
		double CalculateRPN(std::vector<std::string> rpnString);
	};
}

namespace JustHelper
{
	bool IsDigit(char symbol);
	std::vector<std::string> SplitString(std::string str, char symbolForSplit = ' ');	
	std::string Replace(std::string str, char symbolForReplace, std::string symbolForInsert);
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
}
