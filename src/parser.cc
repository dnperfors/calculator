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
    Parser::Parser(const std::string& input)
        : lexer_(input)
    {
        register_prefix(token::LeftParantheses, &Parser::groupParselet);
        register_prefix(token::Number, &Parser::numberParselet);
        register_prefix(token::Identifier, &Parser::identifierParselet);

        int precedence = 0;
        register_infix(token::Assign, &Parser::assignmentParselet, ++precedence);
        register_infix(token::Add, &Parser::binaryOperatorParselet, ++precedence);
        register_infix(token::Subtract, &Parser::binaryOperatorParselet, precedence);
        register_infix(token::Multiply, &Parser::binaryOperatorParselet, ++precedence);
        register_infix(token::Divide, &Parser::binaryOperatorParselet, precedence);
        register_infix(token::Modulo, &Parser::binaryOperatorParselet, precedence);
    }

    Expression_ptr Parser::parseExpression(int precedence)
    {
        auto token = *lexer_;
        ++lexer_;

        auto prefix = prefixParselets_[token.type];
        if(!prefix)
        {
            throw ParserException("Unsupported token...");
        }
        auto left = prefix(token);

        while(precedence < get_precedence((*lexer_).type))
        {
            token = *lexer_;
            ++lexer_;

            auto infix = infixParselets_[token.type];
            left = infix(left, token);
        }
        return left;
    }

    int Parser::get_precedence(token::Type type)
    {
        auto precedence = infixPrecedence_.find(type);
        if(precedence != infixPrecedence_.end())
        {
            return precedence->second;
        }
        return 0;
    }

    template<class F>
    void Parser::register_prefix(token::Type type, F&& function)
    {
        prefixParselets_[type] = std::bind(function, this, std::placeholders::_1);
    }

    template<class F>
    void Parser::register_infix(token::Type type, F&& function, int precedence)
    {
        infixParselets_[type] = std::bind(function, this, std::placeholders::_1, std::placeholders::_2);
        infixPrecedence_[type] = precedence;
    }

    Expression_ptr Parser::numberParselet(token token)
    {
        std::string value(token.value);
        double number = std::atof(value.c_str());
        return std::make_shared<NumberExpression>(number);
    }

    Expression_ptr Parser::identifierParselet(token token)
    {
        std::string value(token.value);
        return std::make_shared<IdentifierExpression>(value);
    }

    Expression_ptr Parser::assignmentParselet(Expression_ptr& left, token)
    {
        auto right = parseExpression();
        return std::make_shared<AssignmentExpression>(left, right);
    }

    BinaryOperatorExpression::Type convertType(token::Type type)
    {
        switch(type)
        {
            case token::Add: return BinaryOperatorExpression::Add;
            case token::Subtract: return BinaryOperatorExpression::Subtract;
            case token::Multiply: return BinaryOperatorExpression::Multiply;
            case token::Divide: return BinaryOperatorExpression::Divide;
            case token::Modulo: return BinaryOperatorExpression::Modulo;
            default: throw ParserException("Unsupported binary operator type.");
        }
    }

    Expression_ptr Parser::binaryOperatorParselet(Expression_ptr& left, token token)
    {
        BinaryOperatorExpression::Type type = convertType(token.type);
        auto right = parseExpression(get_precedence(token.type));

        return std::make_shared<BinaryOperatorExpression>(type, left, right);
    }

    Expression_ptr Parser::groupParselet(token)
    {
        auto expression = parseExpression();
        if((*lexer_).type == token::RightParantheses)
        {
            ++lexer_;
        }
        return expression;
    }
}
