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

#include "lexer.h"

namespace calculator
{
    Lexer::Lexer(const std::string& input)
        : input_(input)
    {
        register_token("[a-zA-Z_][_[:alnum:]]*", token::Identifier);
        register_token("\\=", token::Assign);
        register_token("[[:digit:]]+(.[[:digit:]]+)?", token::Number);
        register_token("\\+", token::Add);
        register_token("\\-", token::Subtract);
        register_token("\\*", token::Multiply);
        register_token("\\/", token::Divide);
        register_token("\\%", token::Modulo);
        register_token("\\(", token::LeftParantheses);
        register_token("\\)", token::RightParantheses);
        register_token("[[:space:]]+", token::WhiteSpace);
        advance();
    }

    bool Lexer::operator!=(const Lexer&) const
    {
        return current_.type != token::EndOfFile;
    }

    void Lexer::operator++()
    {
        advance();
    }

    token Lexer::operator*() const
    {
        return current_;
    }

    void Lexer::advance()
    {
        current_ = next_token();
        if (current_.type == token::WhiteSpace)
        {
            advance();
        }
    }

    token Lexer::next_token()
    {
        for(auto regex : regex_table_)
        {
            std::smatch base_match;
            if(std::regex_search(input_, base_match, regex.first))
            {
                std::string value = base_match[0].str();
                input_ = input_.substr(value.size(), input_.size() - value.size());
                return token(regex.second, value);
            }
        }
        return token();
    }

    void Lexer::register_token(const std::string& regex, token::Type token)
    {
        regex_table_.push_back({ std::regex("^" + regex), token });
    }
}
