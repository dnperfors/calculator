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

#ifndef _CALCULATOR_LEXER_H_
#define _CALCULATOR_LEXER_H_

#include <string>
namespace calculator
{
typedef std::string::const_iterator iterator;

struct token
{
    enum Type { EndOfFile, Identifier, Assign, Number, Add, Subtract, Multiply, Divide, Modulo, LeftParantheses, RightParantheses };

    token() :type(EndOfFile), begin(), end() {}
    token(Type type, iterator& it1, iterator it2)
        :type(type), begin(it1), end(it2){}

    Type type;
    iterator begin;
    iterator end;
};

class Lexer
{
public:
    Lexer(const std::string& input);
    const Lexer& begin() const { return *this; }
    const Lexer& end() const { return *this; }

    bool operator!=(const Lexer&) const;
    void operator++();
    token operator*() const;
private:
    void advance();
    token next_token();
    bool is_character(char c);
    bool is_digit();
    bool is_alpha();
    iterator iterator_;
    token current_;
};

}

#endif
