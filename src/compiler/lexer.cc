#include <lexer.hh>

#define current source[position]


std::vector<Token> Lexer::tokenize()
{
    while (position < source.length()) {
        if (isBlank())
        {
            skipBlank();
        }
        else if (std::isdigit(current.toCodepoint()))
        {
            if (current == "0" && (source[position + 1] == "x" || source[position + 1] == "X"))
            {
                position += 2;
                if (!std::isxdigit(current.toCodepoint()))
                {

                }
            }
        }
        else
        {
            position++;
        }
    }
	return std::vector<Token>();
}

void Lexer::stop(ErrorInfo info)
{
    
}

void Lexer::skipBlank()
{
    while (isBlank())
    {
        position++;
    }
}

expected<Token, ErrorInfo> Lexer::getDecNumber()
{
    bool onceDot = false;
    String left{};
    String right{};
    while (std::isdigit(current.toCodepoint()) || current == "_")
    {
        if (current != "_")
        {
            left += current;
        }
        position++;
    }
    if (current == "n")
    {
        position++;
        return Token{ TokenType::KEYWORD_INTEGER, left };
    }
    if (current == ".")
    {
        onceDot = true;
        right = ".";
    }
    while (std::isdigit(current.toCodepoint()) || current == "_")
    {
        if (current != "_")
        {
            right += current;
        }
        position++;
    }
    String value = left + right;
    if (onceDot && !std::isspace(current.toCodepoint()) && current != "r")
    {
        return ErrorInfo{ INVALID_OR_UNEXPECTED_TOKEN, x, y, value.length() };
    }
    return Token{ TokenType::KEYWORD_DEC_NUMBER, value };
}

expected<Token, ErrorInfo> Lexer::getHexNumber()
{
    bool onceDot = false;
    String left{};
    String right{};
    while (std::isxdigit(current.toCodepoint()) || current == "_")
    {
        if (current != "_")
        {
            left += current;
        }
        position++;
    }
    if (current == "n")
    {
        position++;
        return Token{ TokenType::KEYWORD_INTEGER, left };
    }
    if (current == ".")
    {
        onceDot = true;
        right = ".";
    }
    while (std::isxdigit(current.toCodepoint()) || current == "_")
    {
        if (current != "_")
        {
            right += current;
        }
        position++;
    }
    String value = left + right;
    if (onceDot && !std::isspace(current.toCodepoint()) && current != "r")
    {
        return ErrorInfo{ INVALID_OR_UNEXPECTED_TOKEN, x, y, value.length() };
    }
    return Token{ TokenType::KEYWORD_DEC_NUMBER, value };
}


bool Lexer::isBlank()
{
    switch (current.toCodepoint())
    {
    case '\f': case '\n': case '\r': case '\t': case '\v':
    case 0x20: case 0xa0:
    case 0x1680: case 0x2028: case 0x2029: case 0x202f:
    case 0x205f: case 0x3000: case 0xfeff:
        return true;
    default:
        return false;
    }
}
