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

TEST_CASE("NumberExpression should have correct data")
{
    CHECK(calculator::NumberExpression(0).value == 0);
    CHECK(calculator::NumberExpression(10).value == 10);
    CHECK(calculator::NumberExpression(3.14).value == 3.14);
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
