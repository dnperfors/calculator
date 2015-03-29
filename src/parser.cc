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

#include "expressions.h"
#include "lexer.h"
#include "parser.h"

namespace calculator
{
    Expression_ptr parse(const std::string& input)
    {
        calculator::iterator begin = input.begin();
        calculator::iterator end = input.end();
        std::queue<token> tokens;

        while(begin != end)
        {
            tokens.push(calculator::next_token(begin, end));
        }
        Parser parser(tokens);
        return parser.parseExpression();
    }

    Parser::Parser(std::queue<token> tokens)
        : tokens_(tokens)
    {
        prefixParselets_[token::Number] = std::bind(&Parser::numberParselet, this, std::placeholders::_1);

        infixParselets_[token::Add] = std::bind(&Parser::binaryOperatorParselet, this, std::placeholders::_1, std::placeholders::_2);
        infixParselets_[token::Minus] = std::bind(&Parser::binaryOperatorParselet, this, std::placeholders::_1, std::placeholders::_2);
    }

    int Parser::get_precedence()
    {
        auto token = tokens_.front();
        if(infixParselets_[token.type])
        {
            switch(token.type)
            {
                case token::Add: return 3;
                case token::Minus: return 3;
                default: return 0;
            }
        }
        return 0;
    }

    Expression_ptr Parser::parseExpression(int precedence)
    {
        auto token = tokens_.front();
        tokens_.pop();

        auto prefix = prefixParselets_[token.type];
        if(!prefix)
        {
            throw ParserException("Unsupported token...");
        }
        auto left = prefix(token);

        while(precedence < get_precedence())
        {
            token = tokens_.front();
            tokens_.pop();

            auto infix = infixParselets_[token.type];
            left = infix(left, token);
        }
        return left;
    }

    Expression_ptr Parser::numberParselet(token token)
    {
        std::string value(token.begin, token.end);
        double number = std::atof(value.c_str());
        return std::make_shared<NumberExpression>(number);
    }

    BinaryOperatorExpression::Type convertType(token::Type type)
    {
        switch(type)
        {
            case token::Add: return BinaryOperatorExpression::Add;
            case token::Minus: return BinaryOperatorExpression::Minus;
            default: throw ParserException("Unsupported binary operator type.");
        }
    }
    Expression_ptr Parser::binaryOperatorParselet(Expression_ptr& left, token token)
    {
        BinaryOperatorExpression::Type type = convertType(token.type);
        auto right = parseExpression(3);

        return std::make_shared<BinaryOperatorExpression>(type, left, right);
    }
}
