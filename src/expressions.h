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

#ifndef _CALCULATOR_EXPRESSION_H_
#define _CALCULATOR_EXPRESSION_H_

#include <memory>
#include <string>
#include <sstream>

namespace calculator
{
    struct ExpressionVisitor;
    struct Expression
    {
        virtual void accept(ExpressionVisitor& visitor) = 0;
        virtual std::string str() const = 0;
    };

    using Expression_ptr = std::shared_ptr<Expression>;

    struct NumberExpression : Expression
    {
        NumberExpression (const double literal);
        void accept(ExpressionVisitor& visitor) override;
        std::string str() const override;
        double value;
    };

    struct BinaryOperatorExpression : Expression
    {
        enum Type { Add, Minus, Multiply, Divide };

        BinaryOperatorExpression(Type op, Expression_ptr& left, Expression_ptr& right);
        void accept(ExpressionVisitor& visitor) override;
        std::string str() const override;
        Type op;
        Expression_ptr left;
        Expression_ptr right;
    };

    struct ExpressionVisitor
    {
        virtual void visit(NumberExpression& expression) = 0;
        virtual void visit(BinaryOperatorExpression& expression) = 0;
    };
}

#endif
