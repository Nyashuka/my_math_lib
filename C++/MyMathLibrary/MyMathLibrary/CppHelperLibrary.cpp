#include "CppHelperLibrary.h"

namespace MathExpressions
{
	MathExpression::MathExpression()
	{

	}

	MathExpression::MathExpression(std::string expression)
	{
		_expression = expression;
		_expressionIsInitialized = true;
	}

	MathExpression::~MathExpression()
	{
	}

	void MathExpression::SetArgument(std::string argumentName, double value)
	{
		_arguments[argumentName] = value;
	}

	int MathExpression::GetPriority(std::string operation)
	{
		if (operation == "sin" || operation == "cos" || operation == "tan" || operation == "ctg" || operation == "^")
			return 4;
		if (operation == "*" || operation == "/")
			return 3;
		if (operation == "+" || operation == "-")
			return 2;
		if (operation == "(")
			return 1;
		if (operation == ")")
			return -1;
		if (operation.size() == 1 && isdigit(operation[0]))
			return 0;

		throw std::invalid_argument("Unknown mathematical operation!");
	}

	std::vector<std::string> MathExpression::ExpressionToReversePolishNotation(std::string expression)
	{
		JustHelper::ReplaceAll(expression, " ", "");
		std::vector<std::string> rpnString;
		std::stack<std::string> operators;

		int currentIndex = 0;
		bool isNegative = false;

		for (int i = 0; i < expression.size(); i++)
		{
			if (_operators.find(std::string(1 ,expression[i])) != _operators.end())
			{
				if (expression[i] == '-' && (i == 0 || expression[i - 1] == '('))
				{
					isNegative = true;
					continue;
				}

				while (operators.size() != 0 &&
					GetPriority(std::string(1, expression[i])) < GetPriority(operators.top()))
				{
					rpnString.push_back(operators.top());
					operators.pop();
					currentIndex++;
				}

				operators.push(std::string(1, expression[i]));
			}
			else if (isdigit(expression[i]))
			{
				if (isNegative)
				{
					rpnString.push_back("-" + expression[i]);
					isNegative = false;
				}
				else
				{
					rpnString.push_back(std::string(1, expression[i]));
				}
				while (i + 1 < expression.size() && (isdigit(expression[i + 1]) || expression[i + 1] == '.'))
				{
					i++;
					rpnString[currentIndex] += expression[i];
				}
				currentIndex++;
			}
			else if (isalpha(expression[i]))
			{
				std::string function = "";

				while (i < expression.size())
				{
					function += expression[i];
					if (isalpha(expression[i + 1]) ||isdigit(expression[i + 1]))
						i++;
					else
						break;
				}

				if (IsFunction(function))
				{
					if (i + 1 < expression.size())
					{
						operators.push(function);			
					}

				}
				else if (IsArgument(function))
				{
					if (isNegative)
					{
						rpnString.push_back("-" + function);
						isNegative = false;
					}
					else
					{
						rpnString.push_back(function);
					}
					currentIndex++;
				}

			}
			else if (expression[i] == '(')
			{
				operators.push(std::string(1, expression[i]));
			}
			else if (expression[i] == ')')
			{
				while (operators.top() != "(")
				{
					rpnString.push_back(operators.top());
					operators.pop();
				}
				operators.pop();
			}
		}

		while (operators.size() != 0)
		{
			rpnString.push_back(operators.top());
			operators.pop();
		}
			

		return rpnString;
	}

	double MathExpression::Solve(double firstOperand, double secondOperand, std::string operation)
	{
		if (operation == "+")
		{
			return firstOperand + secondOperand;
		}
		else if (operation == "-")
		{
			return firstOperand - secondOperand;
		}
		else if (operation == "*")
		{
			return firstOperand * secondOperand;
		}
		else if (operation == "/")
		{
			return firstOperand / secondOperand;
		}
		else if (operation == "^")
		{
			return pow(firstOperand, secondOperand);
		}
		else
		{
			throw std::invalid_argument("Unknown mathematical operation!");
		}
	}

	double MathExpression::Solve(double number, std::string function)
	{
		if (function == "sin")
		{
			return sin(number);
		}
		if (function == "cos")
		{
			return cos(number);
		}
		if (function == "tan")
		{
			return tan(number);
		}
		if (function == "ctg")
		{
			return cos(number) / sin(number);
		}
		if (function == "log10")
		{
			return log10(number);
		}
		if (function == "ln")
		{
			return log(number);
		}
		if (function == "lg")
		{
			return log10(number);
		}

		throw std::invalid_argument("Unknown mathematical operation!");
	}

	bool MathExpression::IsNegative(std::string str)
	{
		return str.size() > 1 && str.find("-") == 0;
	}

	bool MathExpression::IsNumber(std::string str)
	{
		bool result = false;
		int index = 0;

		if (IsNegative(str))
			index = 1;

		for (int i = index; i < str.size(); i++)
		{
			if (isdigit(str[i]) || str[i] == '.')
			{
				result = true;
			}
			else
			{
				return false;
			}
		}

		return result;
	}

	bool MathExpression::IsFunction(std::string str)
	{
		return _functions.find(str) != _functions.end();
	}

	bool MathExpression::IsArgument(std::string str)
	{
		if (IsNegative(str))
		{
			str.replace(0, 1, "");
		}

		return _arguments.find(str) != _arguments.end();
	}

	bool MathExpression::IsOperation(std::string str)
	{
		return _operators.find(str) != _operators.end();
	}

	std::vector<std::string> MathExpression::ReplaceArgumentValue(std::vector<std::string> rpnString)
	{
		std::vector<std::string> newRpnString;

		for (auto currentElement : rpnString)
		{
			std::string newCurrentElement = currentElement;

			if (IsArgument(currentElement))
			{
				if (IsNegative(currentElement))
				{
					newCurrentElement = newCurrentElement.replace(0, 1, "");
					if (_arguments[newCurrentElement] <= 0.0)
					{
						newCurrentElement = std::to_string(_arguments[newCurrentElement] * -1);
					}
					else
					{
						newCurrentElement = "-" + std::to_string(_arguments[newCurrentElement]);
					}
				}
				else
				{
					newCurrentElement = std::to_string(_arguments[newCurrentElement]);
				}
			}

			newRpnString.push_back(newCurrentElement);
		}

		return newRpnString;
	}

	double MathExpression::CalculateRPN(std::vector<std::string> rpnString)
	{
		std::vector<std::string> newRpnString = ReplaceArgumentValue(rpnString);
		std::stack<double> numbers;
		double firstOperand;
		double secondOperand;
		double result = 0;
		try
		{
			for (auto element : newRpnString)
			{
				if (IsNumber(element))
				{
					numbers.push(std::stod(element));
				}
				else if (IsOperation(element))
				{
					secondOperand = numbers.top();
					numbers.pop();
					firstOperand = numbers.top();
					numbers.pop();

					result = Solve(firstOperand, secondOperand, element);
					numbers.push(result);
				}
				else if (IsFunction(element))
				{
					firstOperand = numbers.top();
					numbers.pop();

					result = Solve(firstOperand, element);

					numbers.push(result);
				}

			}
		}
		catch (std::exception)
		{
			return NAN;
		}


		return result;
	}

	double MathExpression::Calculate()
	{
		if (!_expressionIsInitialized)
			throw std::invalid_argument("Expression not set!");

		return CalculateRPN(ExpressionToReversePolishNotation(_expression));
	}

	double MathExpression::Calculate(std::string expression)
	{
		return CalculateRPN(ExpressionToReversePolishNotation(expression));
	}
}

namespace JustHelper
{
	bool IsDigit(char symbol)
	{
		return false;
	}

	std::vector<std::string> SplitString(std::string str, char symbolForSplit)
	{
		std::vector<std::string> allData;
		std::string buffer = "";
		for (const auto& c : str)
		{
			if (c != symbolForSplit)
			{
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

	bool Replace(std::string& str, const std::string& from, const std::string& to) 
	{
		size_t start_pos = str.find(from);

		if (start_pos == std::string::npos)
			return false;

		str.replace(start_pos, from.length(), to);

		return true;
	}

	void ReplaceAll(std::string& str, const std::string& from, const std::string& to) 
	{	
		if (from.empty())
			return;

		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) 
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}

}