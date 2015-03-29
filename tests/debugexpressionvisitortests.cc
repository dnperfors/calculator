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

#include <catch.hpp>

#include <map>

#include <expressions.h>
#include <debugexpressionvisitor.h>

TEST_CASE("Should return single value from NumberExpression")
{
    calculator::DebugExpressionVisitor visitor;
    calculator::NumberExpression expression(3.14);
    expression.accept(visitor);
    CHECK(visitor.result() == "(NumberExpression: 3.14)");
}

TEST_CASE("Should return string representation of an binary expression")
{
    std::map<calculator::BinaryOperatorExpression::Type, std::string> testdata {
        { calculator::BinaryOperatorExpression::Add, "(BinaryOperatorExpression: (NumberExpression: 3.14) + (NumberExpression: 3.14))" },
        { calculator::BinaryOperatorExpression::Minus, "(BinaryOperatorExpression: (NumberExpression: 3.14) - (NumberExpression: 3.14))" }
    };
    calculator::Expression_ptr left = std::make_shared<calculator::NumberExpression>(3.14);
    calculator::Expression_ptr right = std::make_shared<calculator::NumberExpression>(3.14);
    for(auto pair : testdata)
    {
        calculator::DebugExpressionVisitor visitor;
        calculator::Expression_ptr expression = std::make_shared<calculator::BinaryOperatorExpression>(pair.first, left, right);
        expression->accept(visitor);
        CHECK(visitor.result() == pair.second);
    }
}

