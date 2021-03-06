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

#include <map>
#include "expressions.h"

namespace calculator
{
    NumberExpression::NumberExpression(const double number)
        : value(number)
    {
    }

    void NumberExpression::accept(ExpressionVisitor& visitor)
    {
        visitor.visit(*this);
    }

    std::string NumberExpression::str() const
    {
        std::stringstream s;
        s << value;
        return s.str();
    }

    IdentifierExpression::IdentifierExpression(const std::string& identifier)
        : value(identifier)
    {
    }

    void IdentifierExpression::accept(ExpressionVisitor& visitor)
    {
        visitor.visit(*this);
    }

    std::string IdentifierExpression::str() const
    {
        return value;
    }

    AssignmentExpression::AssignmentExpression(Expression_ptr& left, Expression_ptr& right)
        : left(left), right(right)
    {
    }

    std::string AssignmentExpression::str() const
    {
        std::stringstream s;
        s << left->str() << " = " << right->str();
        return s.str();
    }

    void AssignmentExpression::accept(ExpressionVisitor& visitor)
    {
        visitor.visit(*this);
    }

    BinaryOperatorExpression::BinaryOperatorExpression(Type op, Expression_ptr& left, Expression_ptr& right)
        : op(op), left(left), right(right)
    {
    }

    void BinaryOperatorExpression::accept(ExpressionVisitor& visitor)
    {
        visitor.visit(*this);
    }

    const std::map<BinaryOperatorExpression::Type, char> op_text_map {
        { BinaryOperatorExpression::Add, '+' },
        { BinaryOperatorExpression::Subtract, '-' },
        { BinaryOperatorExpression::Multiply, '*' },
        { BinaryOperatorExpression::Divide, '/' },
        { BinaryOperatorExpression::Modulo, '%' },
    };

    std::string BinaryOperatorExpression::str() const
    {
        std::stringstream s;
        s << "(" << left->str() << " " << op_text_map.at(op) << " " << right->str() << ")";
        return s.str();
    }
}
