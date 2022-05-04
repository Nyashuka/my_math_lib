using Aveezan.MathExpressions;

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
            string expression2 = "-5";

            Argument argument = new Argument("x");
            argument.setArgumentValue(-5);
            Expression mxParser = new Expression(expression2, argument);

            MathExpression calculator = new MathExpression(expression2);
            calculator.SetArgument("x", -5);
            

            Console.WriteLine("\nMxParse Result: " + mxParser.calculate());
            Console.WriteLine("\nMy Result: " + calculator.Calculate());
            //Console.WriteLine("\nC# Result: " + Math.Log10(10));

        }
    }
}
