// EvalExpression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Evaluator.h"
#include <iostream>

void Test(const char* text)
{
   Parser parser;

   try 
   {
      ASTNode* ast = parser.Parse(text);

      try 
      {
         Evaluator eval;
         double val = eval.Evaluate(ast);

         std::cout << text << " = " << val << std::endl;
      }
      catch(EvaluatorException& ex)
      {
		  std::cout << text << " \t " << ex.what() << std::endl; 
      }

      delete ast;
   }
   catch(ParserException& ex)
   {
      std::cout << text << " \t " << ex.what() << std::endl; 
   }   
}

int main(int argc, _TCHAR* argv[])
{
   Test("1+2+3+4");
   Test("1*2*3*4");
   Test("1-2-3-4");
   Test("1/2/3/4");
   Test("1*2+3*4");
   Test("1+2*3+4");
   Test("(1+2)*(3+4)");
   Test("1+(2*3)*(4+5)");
   Test("1+(2*3)/4+5");
   Test("5/(4+3)/2");
   Test("1 + 2.5");
   Test("125");
   Test("-1");
   Test("-1+(-2)");
   Test("-1+(-2.0)");

   Test("   1*2,5");
   Test("   1*2.5e2");
   Test("M1 + 2.5");
   Test("1 + 2&5");
   Test("1 * 2.5.6");
   Test("1 ** 2.5");
   Test("*1 / 2.5");

   return 0;
}

