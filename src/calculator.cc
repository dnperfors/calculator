/*
 * Copyright (C) 2015 David Perfors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>

#include <parser.h>
#include <calculatorvisitor.h>

int main(int, char**)
{
    std::cout << "Welcome to calculator, please enter your expression" << std::endl;
    while(true)
    {
        std::string input;
        getline(std::cin, input);
        std::cout << "Input was: " << input << std::endl;

        if(input == "quit")
        {
            break;
        }
        auto expression = calculator::Parser(input).parseExpression();
        
        std::cout << "Expression parsed as: " << expression->str() << std::endl;

        calculator::CalculatorVisitor visitor;
        expression->accept(visitor);

        std::cout << "Result: " << visitor.result() << std::endl;
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}
