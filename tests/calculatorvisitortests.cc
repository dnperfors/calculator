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
#include <calculatorvisitor.h>

TEST_CASE("Should be able to calculate add function")
{
    auto expression = calculator::Parser("1 + 1").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 2.0);
}

TEST_CASE("Should be able to calculate min function")
{
    auto expression = calculator::Parser("3 - 1").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 2.0);
}

TEST_CASE("Should be able to calculate multiply function")
{
    auto expression = calculator::Parser("3 * 2").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 6.0);
}

TEST_CASE("Should be able to calculate divide function")
{
    auto expression = calculator::Parser("4 / 2").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 2.0);
}

TEST_CASE("Should be able to calculate modulo function")
{
    auto expression = calculator::Parser("4 % 3").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 1.0);
}

TEST_CASE("Should be able to calculate complex functions")
{
    auto expression = calculator::Parser("1 + 3 * 2").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 7.0);
}

TEST_CASE("Should register identifiers")
{
    auto expression = calculator::Parser("a").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    CHECK(variableMap.size() == 1);
    CHECK(variableMap.at("a") == 0);
}

TEST_CASE("Should not register identifier twice")
{
    auto expression = calculator::Parser("a+a").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    CHECK(variableMap.size() == 1);
    CHECK(variableMap.at("a") == 0);
}

TEST_CASE("Shoud get correct value when variable has value")
{
    auto expression = calculator::Parser("a+a").parseExpression();
    std::map<std::string, double> variableMap;
    variableMap["a"] = 1;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(visitor.result() == 2.0);
}

TEST_CASE("Should assign value to variable")
{
    auto expression = calculator::Parser("a = 1").parseExpression();
    std::map<std::string, double> variableMap;
    calculator::CalculatorVisitor visitor(variableMap);
    expression->accept(visitor);
    REQUIRE(variableMap["a"] == 1.0);
}
