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
#include <vector>
#include <lexer.h>

calculator::token get_single_token(const std::string& input)
{
    for(auto token : calculator::Lexer(input))
    {
        return token;
    }
    return calculator::token();
}

void check_single_token(const std::string& input, calculator::token::Type expectedType)
{
    auto output = get_single_token(input);
    CHECK(output.type == expectedType);
    CHECK(std::string(output.begin, output.end) == input);
}

void check_multiple_tokens(const std::vector<std::string> testdata, calculator::token::Type expectedType)
{
    for(std::string input : testdata)
    {
        check_single_token(input, expectedType);
    }
}

void check_multiple_tokens(const std::map<std::string, calculator::token::Type> testdata)
{
    for(auto input : testdata)
    {
        check_single_token(input.first, input.second);
    }
}

TEST_CASE("Should get Number token for different kind of numbers")
{
    check_multiple_tokens({ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }, calculator::token::Number);
    check_multiple_tokens({ "99", "412", "987321654" }, calculator::token::Number);
    check_multiple_tokens({ "1.25", "3.14" }, calculator::token::Number);
}

TEST_CASE("Should get correct token for single character operators")
{
    check_multiple_tokens({ 
        { "+", calculator::token::Add },
        { "-", calculator::token::Subtract },
        { "*", calculator::token::Multiply },
        { "/", calculator::token::Divide },
        { "(", calculator::token::LeftParantheses },
        { ")", calculator::token::RightParantheses },
    });
}

TEST_CASE("Should ignore spaces between tokens")
{
    std::string input(" 1 + 1 ");
    calculator::Lexer lexer(input);

    CHECK((*lexer).type == calculator::token::Number);
    ++lexer;
    CHECK((*lexer).type == calculator::token::Add);
    ++lexer;
    CHECK((*lexer).type == calculator::token::Number);
}
