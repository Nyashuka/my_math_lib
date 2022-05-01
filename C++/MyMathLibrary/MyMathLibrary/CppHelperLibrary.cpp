#include "CppHelperLibrary.h"



namespace MathExpressions
{
	MathExpression::MathExpression()
	{
	}
	MathExpression::MathExpression(std::string expression)
	{
	}
	void MathExpression::SetArgument(std::string, double value)
	{
	}
	double MathExpression::Calculate()
	{
		return 0.0;
	}
	double MathExpression::Calculate(std::string expression)
	{
		return 0.0;
	}

	int MathExpression::GetPriority(std::string operation)
	{
		return 0;
	}

	std::vector<std::string> MathExpression::ExpressionToReversePolishNotation(std::string expression)
	{
		return std::vector<std::string>();
	}

	double MathExpression::Solve(double firstOperand, double secondOperand, std::string operation)
	{
		return 0.0;
	}

	double MathExpression::Solve(double number, std::string function)
	{
		return 0.0;
	}

	bool MathExpression::IsNegative(std::string str)
	{
		return false;
	}

	bool MathExpression::IsNumber(std::string str)
	{
		return false;
	}

	bool MathExpression::IsFunction(std::string str)
	{
		return false;
	}

	bool MathExpression::IsArgument(std::string str)
	{
		return false;
	}

	bool MathExpression::IsOperation(std::string str)
	{
		return false;
	}

	void MathExpression::ReplaceArgumentValue(std::vector<std::string> rpnString)
	{
	}

	double MathExpression::CalculateRPN(std::vector<std::string> rpnString)
	{
		return 0.0;
	}

}


namespace JustHelper 
{
	std::vector<std::string> SplitString(std::string str, char symbolForSplit)
	{
		std::vector<std::string> allData;
		std::string buffer = "";
		for (const auto& c : str)
		{
			if (c != symbolForSplit) {
				buffer += c;
			}
			else
			{
				allData.push_back(buffer);
				buffer.clear();
			}
		}
		allData.push_back(buffer);
		return allData;
	}
}