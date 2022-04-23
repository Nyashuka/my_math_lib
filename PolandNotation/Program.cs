using Aveezan.Math.Expressions;

using org.mariuszgromada.math.mxparser;
using System;
using System.Collections.Generic;


namespace PolishNotation
{
    public class Program
    {

        /*
         2*(-2)
         
        curr: 2,  
        stack: * ( 
         */

        /*
         1-(-4 * (-3))
         
        curr: 2,  
        stack: * ( 
         */




        /*
         
         4*12+(-3-5)
         
         curr: 4, 12, -3, 5, *, +
         stack: * +

         stack: 4 2 -8

     
         */

        static void Main(string[] args)
        {
            string expression = "1.5-x^(1-cos(x))";
            string expression1 = "3*x^(3/5)+1";
            string expression2 = "lg(10)";

            Argument argument = new Argument("x");
            argument.setArgumentValue(1);
            Expression mxParser = new Expression(expression2, argument);

            MathExpression calculator = new MathExpression(expression2);
            calculator.SetArgument("x", 1);
            

            Console.WriteLine("\nResult: " + mxParser.calculate());
            Console.WriteLine("\nResult: " + calculator.Calculate());
            Console.WriteLine("\nResult: " + Math.Log10(10));

        }
    }
}
