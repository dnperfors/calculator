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

#include <map>
#include "lexer.h"

namespace calculator
{
    std::map<char, token::Type> single_character_tokens {
        { '=', token::Assign },
        { '+', token::Add },
        { '-', token::Subtract },
        { '*', token::Multiply },
        { '/', token::Divide },
        { '%', token::Modulo },
        { '(', token::LeftParantheses },
        { ')', token::RightParantheses },
    };

    Lexer::Lexer(const std::string& input)
        : iterator_(input.begin())
    {
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
    }

    token Lexer::next_token()
    {
        iterator it = iterator_;
        if(is_character(' '))
        {
            ++it;
            ++iterator_;
        }
        if(single_character_tokens.find(*iterator_) != single_character_tokens.end())
        {
            ++iterator_;
            return token(single_character_tokens.at(*it), it, iterator_); 
        }
        if(is_digit())
        {
            do
            {
                ++iterator_;
            }
            while(is_digit() || is_character('.'));
            return token(token::Number, it, iterator_);
        }
        if(is_alpha() || is_character('_'))
        {
            do
            {
                ++iterator_;
            }
            while(is_alpha() || is_digit() || is_character('_'));
            return token(token::Identifier, it, iterator_);
        }
        return token();
    }
    
    bool Lexer::is_character(char c)
    {
        return *iterator_ == c;
    }

    bool Lexer::is_digit()
    {
        return (*iterator_ >= '0' && *iterator_ <= '9');
    }
    
    bool Lexer::is_alpha()
    {
        return
            (*iterator_ >= 'A' && *iterator_ <= 'Z') ||
            (*iterator_ >= 'a' && *iterator_ <= 'z');
    }
}
