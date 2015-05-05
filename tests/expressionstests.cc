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

TEST_CASE("NumberExpression should show correct str")
{
    CHECK(calculator::NumberExpression(0).str() == "0");
    CHECK(calculator::NumberExpression(10).str() == "10");
    CHECK(calculator::NumberExpression(3.14).str() == "3.14");
}
TEST_CASE("NumberExpression should have correct data")
{
    CHECK(calculator::NumberExpression(0).value == 0);
    CHECK(calculator::NumberExpression(10).value == 10);
    CHECK(calculator::NumberExpression(3.14).value == 3.14);
}

TEST_CASE("IdentifierExpression should show correct str")
{
    CHECK(calculator::IdentifierExpression("x").str() == "x");
    CHECK(calculator::IdentifierExpression("x1").str() == "x1");
    CHECK(calculator::IdentifierExpression("_id").str() == "_id");
}
TEST_CASE("IdentifierExpression should have correct data")
{
    CHECK(calculator::IdentifierExpression("x").value == "x");
    CHECK(calculator::IdentifierExpression("x1").value == "x1");
    CHECK(calculator::IdentifierExpression("_id").value == "_id");
}
TEST_CASE("AssignmentExpression should show correct str")
{
    calculator::Expression_ptr left = std::make_unique<calculator::IdentifierExpression>("x");
    calculator::Expression_ptr right = std::make_unique<calculator::NumberExpression>(1);
    calculator::AssignmentExpression expression(left, right);
    CHECK(expression.str() == "x = 1");
}

TEST_CASE("OperatorExpression should show correct str")
{
    std::map<calculator::BinaryOperatorExpression::Type, std::string> testdata { 
        { calculator::BinaryOperatorExpression::Add, "(1 + 1)" },
        { calculator::BinaryOperatorExpression::Subtract, "(1 - 1)" },
        { calculator::BinaryOperatorExpression::Multiply, "(1 * 1)" },
        { calculator::BinaryOperatorExpression::Divide, "(1 / 1)" },
    };

    calculator::Expression_ptr left = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr right = std::make_unique<calculator::NumberExpression>(1);
    for(auto input : testdata)
    {
        calculator::BinaryOperatorExpression expression(input.first, left, right);
        CHECK(expression.str() == input.second);
    }
}
TEST_CASE("OperatorExpression should have correct data")
{
    calculator::Expression_ptr left = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr right = std::make_unique<calculator::NumberExpression>(1);
    calculator::BinaryOperatorExpression expression(calculator::BinaryOperatorExpression::Add, left, right);
    CHECK(expression.op == calculator::BinaryOperatorExpression::Add);
    CHECK(expression.left == left);
    CHECK(expression.right == right);
}
TEST_CASE("OperatorExpression should show correct str with multiple expressions 1.")
{
    calculator::Expression_ptr leftFirst = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr leftSecond = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr left = std::make_unique<calculator::BinaryOperatorExpression>(calculator::BinaryOperatorExpression::Add, leftFirst, leftSecond);
    calculator::Expression_ptr right= std::make_unique<calculator::NumberExpression>(2);
    auto expression = std::make_unique<calculator::BinaryOperatorExpression>(calculator::BinaryOperatorExpression::Multiply, left, right);
    CHECK(expression->str() == "((1 + 1) * 2)");
}
TEST_CASE("OperatorExpression should show correct str with multiple expressions 2.")
{
    calculator::Expression_ptr leftFirst = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr leftSecond = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr left = std::make_unique<calculator::BinaryOperatorExpression>(calculator::BinaryOperatorExpression::Add, leftFirst, leftSecond);
    calculator::Expression_ptr rightFirst = std::make_unique<calculator::NumberExpression>(2);
    calculator::Expression_ptr rightSecond = std::make_unique<calculator::NumberExpression>(1);
    calculator::Expression_ptr right = std::make_unique<calculator::BinaryOperatorExpression>(calculator::BinaryOperatorExpression::Subtract, rightFirst, rightSecond);
    auto expression = std::make_unique<calculator::BinaryOperatorExpression>(calculator::BinaryOperatorExpression::Multiply, left, right);
    CHECK(expression->str() == "((1 + 1) * (2 - 1))");

}
