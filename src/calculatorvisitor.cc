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

#include "calculatorvisitor.h"

namespace calculator
{
    CalculatorVisitor::CalculatorVisitor()
        :result_(0)
    {
    }

    void CalculatorVisitor::visit(NumberExpression& expression)
    {
        result_ = expression.value;
    }

    void CalculatorVisitor::visit(BinaryOperatorExpression& expression)
    {
        CalculatorVisitor visitorLeft;
        expression.left->accept(visitorLeft);
        float left = visitorLeft.result();
        CalculatorVisitor visitorRight;
        expression.right->accept(visitorRight);
        float right = visitorRight.result();
        switch(expression.op)
        {
            case BinaryOperatorExpression::Add:
                result_ = left + right;
                break;
            case BinaryOperatorExpression::Minus:
                result_ = left - right;
                break;
            case BinaryOperatorExpression::Multiply:
                result_ = left * right;
                break;
            case BinaryOperatorExpression::Divide:
                result_ = left / right;
                break;
            default:
                result_ = 0;
                break;
        }
    }
}
