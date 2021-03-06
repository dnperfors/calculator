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
#include <parser.h>

calculator::Expression_ptr parse(const std::string& input)
{
    return calculator::Parser(input).parseExpression();
}

TEST_CASE("Should throw exception when expression is invalid")
{
    REQUIRE_THROWS_AS(parse(""), calculator::ParserException);
}

TEST_CASE("Should get correct expression from a number")
{
    CHECK(parse("0")->str() == "0");
    CHECK(parse("100")->str() == "100");
    CHECK(parse("101.13")->str() == "101.13");
}

TEST_CASE("Should get correct expression from identifier")
{
    CHECK(parse("x")->str() == "x");
    CHECK(parse("x1")->str() == "x1");
    CHECK(parse("_it")->str() == "_it");
}

TEST_CASE("Should get correct expression from multiple tokens")
{
    CHECK(parse(" x + 1")->str() == "(x + 1)");
    CHECK(parse(" y - 1")->str() == "(y - 1)");
    CHECK(parse(" x * 1")->str() == "(x * 1)");
    CHECK(parse(" y / 1")->str() == "(y / 1)");
    CHECK(parse("3 % 2")->str() == "(3 % 2)");
}

TEST_CASE("Should get correct precedence of expressions")
{
    CHECK(parse("1 + 1 - 1")->str() == "((1 + 1) - 1)");
    CHECK(parse("1 - 1 + 1")->str() == "((1 - 1) + 1)");
    CHECK(parse("1 + 1 * 1")->str() == "(1 + (1 * 1))");
    CHECK(parse("1 + 1 / 1")->str() == "(1 + (1 / 1))");
    CHECK(parse("1 + 1 % 1")->str() == "(1 + (1 % 1))");
    CHECK(parse("1 * 1 - 1")->str() == "((1 * 1) - 1)");
    CHECK(parse("1 / 1 - 1")->str() == "((1 / 1) - 1)");
    CHECK(parse("1 % 1 - 1")->str() == "((1 % 1) - 1)");

    CHECK(parse("1 + 1 * 1 - 1")->str() == "((1 + (1 * 1)) - 1)");
    CHECK(parse("(1 + 1) * (1 - 1)")->str() == "((1 + 1) * (1 - 1))");
}

TEST_CASE("Should get correct expression for assignment")
{
    CHECK(parse("x = 1 + 1")->str() == "x = (1 + 1)");
}
