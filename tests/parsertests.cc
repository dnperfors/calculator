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

#include <expressions.h>
#include <debugexpressionvisitor.h>
#include <parser.h>

calculator::Expression_ptr parse(const std::string& input)
{
    return calculator::Parser(input).parseExpression();
}

std::string str(calculator::Expression_ptr expression)
{
    calculator::DebugExpressionVisitor visitor;
    expression->accept(visitor);
    return visitor.result();
}

TEST_CASE("Should throw exception when expression is invalid")
{
    REQUIRE_THROWS_AS(parse(""), calculator::ParserException);
}

TEST_CASE("Should get correct expression from a number")
{
    CHECK(str(parse("0")) == "(NumberExpression: 0)");
    CHECK(str(parse("100")) == "(NumberExpression: 100)");
    CHECK(str(parse("101.13")) == "(NumberExpression: 101.13)");
}

TEST_CASE("Should get correct expression from multiple tokens")
{
    CHECK(str(parse(" 1 + 1")) == "(BinaryOperatorExpression: (NumberExpression: 1) + (NumberExpression: 1))");
    CHECK(str(parse(" 1 - 1")) == "(BinaryOperatorExpression: (NumberExpression: 1) - (NumberExpression: 1))");
}

TEST_CASE("Should get correct precedence of expressions")
{
    CHECK(str(parse("1 + 1 - 1")) == "(BinaryOperatorExpression: (BinaryOperatorExpression: (NumberExpression: 1) + (NumberExpression: 1)) - (NumberExpression: 1))");
}
