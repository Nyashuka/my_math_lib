using System;
using System.Collections.Generic;


namespace Aveezan.MathExpressions
{
    public class MathExpression
    {
        private readonly List<string> _operators = new List<string>() { "+", "-", "/", "*", "^" };
        private readonly List<string> _functions = new List<string>() { "sin", "cos", "tan", "ctg", "ln", "log", "lg", "log10" };
        private Dictionary<string, double> _arguments;
        private string _expression = "";

        public MathExpression()
        {
            _arguments = new Dictionary<string, double>();
        }

        public MathExpression(string expression) : this()
        {
            _expression = expression;

        }

        public void SetArgument(string name, double value)
        {
            if (_arguments.ContainsKey(name))
                _arguments[name] = value;
            else
                _arguments.Add(name, value);
        }

        private int GetPriority(string operation)
        {
            if (operation == "sin" || operation == "cos" || operation == "tan" || operation == "ctg" || operation == "^")
                return 3;
            if (operation == "*" || operation == "/")
                return 3;
            if (operation == "+" || operation == "-")
                return 2;
            if (operation == "(")
                return 1;
            if (operation == ")")
                return -1;
            if (operation.Length == 1 && Char.IsDigit(Convert.ToChar(operation)))
                return 0;

            throw new Exception("Unknown mathematical operation!");
        }


        private List<string> ExpressionToReversePolishNotation(string expression)
        {
            expression = expression.Replace(" ", "");
            List<string> rpnString = new List<string>(); ;
            Stack<string> operators = new Stack<string>();

            int currentIndex = 0;
            bool isNegative = false;

            for (int i = 0; i < expression.Length; i++)
            {
                if (_operators.Contains(expression[i].ToString()))
                {
                    if (expression[i] == '-' && (expression[i - 1] == '(' || i == 0))
                    {
                        isNegative = true;
                        continue;
                    }

                    while (operators.Count != 0 &&
                          GetPriority(expression[i].ToString()) < GetPriority(operators.Peek()))
                    {
                        rpnString.Add(operators.Pop());
                        currentIndex++;
                    }

                    operators.Push(expression[i].ToString());
                }
                else if (Char.IsDigit(expression[i]))
                {
                    if (isNegative)
                    {
                        rpnString.Add("-" + expression[i].ToString());
                        isNegative = false;
                    }
                    else
                    {
                        rpnString.Add(expression[i].ToString());
                    }
                    while (i + 1 < expression.Length && (Char.IsDigit(expression[i + 1]) || expression[i + 1] == '.'))
                    {
                        i++;
                        rpnString[currentIndex] += expression[i];
                    }
                    currentIndex++;
                }
                else if (Char.IsLetter(expression[i]))
                {
                    string function = "";

                    while (i < expression.Length)
                    {
                        function += expression[i];
                        if (Char.IsLetter(expression[i + 1]) || Char.IsDigit(expression[i + 1]))
                            i++;
                        else
                            break;
                    }

                    if (IsFunction(function))
                    {
                        if (i + 1 < expression.Length)
                        {
                            operators.Push(function);
                            //operators.Push(expression[i+1].ToString());
                        }

                    }
                    else if (IsArgument(function))
                    {
                        if (isNegative)
                        {
                            rpnString.Add("-" + function);
                            isNegative = false;
                        }
                        else
                        {
                            rpnString.Add(function);
                        }
                        currentIndex++;
                    }

                }
                else if (expression[i] == '(')
                {
                    operators.Push(expression[i].ToString());
                }
                else if (expression[i] == ')')
                {
                    while (operators.Peek() != "(")
                    {
                        rpnString.Add(operators.Pop());
                    }
                    operators.Pop();
                }
            }

            while (operators.Count != 0)
                rpnString.Add(operators.Pop());

            return rpnString;
        }

        private double Solve(double firstOperand, double secondOperand, string operation)
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
                return Math.Pow(firstOperand, secondOperand);
            }
            else
            {
                throw new Exception("Unknown mathematical operation!");
            }
        }

        private double Solve(double number, string function)
        {
            if (function == "sin")
            {
                return Math.Sin(number);
            }
            else if (function == "cos")
            {
                return Math.Cos(number);
            }
            else if (function == "tan")
            {
                return Math.Tan(number);
            }
            else if (function == "ctg")
            {
                return Math.Cos(number) / Math.Sin(number);
            }
            else if (function == "log10")
            {
                return Math.Log10(number);
            }
            else if (function == "ln")
            {
                return Math.Log(number);
            }
            else if (function == "lg")
            {
                return Math.Log10(number);
            }
            else
            {
                throw new Exception("Unknown mathematical operation!");
            }
        }

        private bool IsNegative(string str)
        {
            return str.Length > 1 && str.IndexOf("-") == 0;
        }

        private bool IsNumber(string str)
        {
            bool result = false;
            int index = 0;
            if (IsNegative(str))
                index = 1;

            for (int i = index; i < str.Length; i++)
            {
                if (Char.IsNumber(str[i]) || str[i] == '.')
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

        private bool IsFunction(string str)
        {
            return _functions.Contains(str);
        }

        private bool IsArgument(string str)
        {
            return _arguments.ContainsKey(IsNegative(str) ? str.Replace("-", "") : str);
        }

        private bool IsOperation(string str)
        {
            return _operators.Contains(str);
        }

        private void ReplaceArgumentValue(List<string> rpnString)
        {
            for (int i = 0; i < rpnString.Count; i++)
            {
                if (IsArgument(rpnString[i]))
                {
                    string number = "";
                    if (IsNegative(rpnString[i]))
                    {
                        number = rpnString[i][1].ToString();
                        number = number.Replace(number, Convert.ToString(_arguments[number]));
                        number = "-" + number;
                    }
                    else
                    {
                        number = rpnString[i].Replace(rpnString[i], Convert.ToString(_arguments[rpnString[i]]));
                    }

                    rpnString[i] = number;
                }
            }
        }

        private double CalculateRPN(List<string> rpnString)
        {
            ReplaceArgumentValue(rpnString);
            Stack<double> numbers = new Stack<double>();
            double firstOperand;
            double secondOperand;
            double result = 0;
            try
            {
                foreach (var element in rpnString)
                {
                    if (IsNumber(element))
                    {
                        numbers.Push(Convert.ToDouble(element));
                    }
                    else if (IsOperation(element))
                    {
                        secondOperand = numbers.Pop();
                        firstOperand = numbers.Pop();

                        result = Solve(firstOperand, secondOperand, element);
                        numbers.Push(result);
                    }
                    else if (IsFunction(element))
                    {
                        firstOperand = numbers.Pop();

                        result = Solve(firstOperand, element);

                        numbers.Push(result);
                    }

                }
            }
            catch (Exception)
            {

                return double.NaN;
            }


            return result;
        }

        public double Calculate()
        {
            if (_expression.Length < 1)
                throw new Exception("Expression not specified!");

            return CalculateRPN(ExpressionToReversePolishNotation(_expression));
        }

        public double Calculate(string expression)
        {
            return CalculateRPN(ExpressionToReversePolishNotation(expression));
        }

    }
}
