#include <lexer.hh>

#define current source[position]

static std::pair<size_t, size_t> findLineAndColumn(const String& text, size_t index) {

    size_t line = 1;
    size_t column = 1;
    for (size_t i = 0; i < index; ++i) {
        if (text[i] == '\n') {
            line++;
            column = 1;
        }
        else {
            column++;
        }
    }

    return std::make_pair(line, column);
}

static std::map<String, TokenType> keywords = {
    { "if", TokenType::KEYWORD_IF },
    { "else", TokenType::KEYWORD_ELSE },
    { "switch", TokenType::KEYWORD_SWITCH },
    { "case", TokenType::KEYWORD_CASE },
    { "default", TokenType::KEYWORD_DEFAULT },
    { "while", TokenType::KEYWORD_WHILE },
    { "for", TokenType::KEYWORD_FOR },
    { "return", TokenType::KEYWORD_RETURN },
    { "break", TokenType::KEYWORD_BREAK },
    { "continue", TokenType::KEYWORD_CONTINUE },
    { "match", TokenType::KEYWORD_MATCH },
    { "let", TokenType::KEYWORD_LET_DECLARATION },
    { "const", TokenType::KEYWORD_CONST_DECLARATION },
    { "range", TokenType::KEYWORD_RANGE },
};

static std::map<String, TokenType> operatorMap = {
    { "+", TokenType::OPERATOR_ADD },
    { "-", TokenType::OPERATOR_SUBTRACT },
    { "*", TokenType::OPERATOR_MULTIPLY },
    { "/", TokenType::OPERATOR_DIVIDE },
    { "%", TokenType::OPERATOR_MODULUS },
    { "=", TokenType::OPERATOR_ASSIGN },
    { "+=", TokenType::OPERATOR_ADD_ASSIGN },
    { "-=", TokenType::OPERATOR_SUBTRACT_ASSIGN },
    { "*=", TokenType::OPERATOR_MULTIPLY_ASSIGN },
    { "/=", TokenType::OPERATOR_DIVIDE_ASSIGN },
    { "%=", TokenType::OPERATOR_MODULUS_ASSIGN },
    { "<<", TokenType::OPERATOR_LEFT_SHIFT },
    { ">>", TokenType::OPERATOR_RIGHT_SHIFT },
    { "<<=", TokenType::OPERATOR_LEFT_SHIFT_ASSIGN },
    { ">>=", TokenType::OPERATOR_RIGHT_SHIFT_ASSIGN },
    { "==", TokenType::OPERATOR_EQUALS },
    { "!=", TokenType::OPERATOR_NOT_EQUALS },
    { "<", TokenType::OPERATOR_LESS_THAN },
    { ">", TokenType::OPERATOR_GREATER_THAN },
    { "<=", TokenType::OPERATOR_LESS_THAN_OR_EQUAL },
    { ">=", TokenType::OPERATOR_GREATER_THAN_OR_EQUAL },
    { "**", TokenType::OPERATOR_EXPONENT },
    { "&&", TokenType::OPERATOR_LOGICAL_AND },
    { "||", TokenType::OPERATOR_LOGICAL_OR },
    { "!", TokenType::OPERATOR_LOGICAL_NOT },
    { "&", TokenType::OPERATOR_BITWISE_AND },
    { "|", TokenType::OPERATOR_BITWISE_OR },
    { "^", TokenType::OPERATOR_BITWISE_XOR },
    { "~", TokenType::OPERATOR_BITWISE_NOT },
    { "?", TokenType::OPERATOR_QUESTION },
    { ":", TokenType::OPERATOR_COLON },
    { "->", TokenType::KEYWORD_ARROW_CASE },
    { "=>", TokenType::KEYWORD_ARROW_FUNCTION },
};

std::vector<Token> Lexer::tokenize()
{
    while (position < source.length()) {
        if (isBlank())
        {
            skipBlank();
        }

        // Keyword or Identifier
        else if (isWord(false))
        {
            push(getWord());
        }
        else if (isOperatorStart())
        {
            push(getOperator());
        }

        // Number
        else if (std::isdigit(current.toCodepoint()))
        {
            if (current == "0" && (source[position + 1] == "x" || source[position + 1] == "X"))
            {
                position += 2;
                if (!std::isxdigit(current.toCodepoint()))
                {
                    auto _ = findLineAndColumn(source, position);
                    stop({ INVALID_OR_UNEXPECTED_TOKEN, _.first, _.second, 2 });
                }
                push(getHexNumber());
            }
            else
            {
                push(getDecNumber());
            }
            position++;
        }

        // String
        else if (current == '"')
        {
            position++;
            String strValue;
            while (current != '"' && position < source.length()) {
                if (current == '\\' && position + 1 < source.length()) {
                    position++;
                    Char nextChar = current;
                    switch (nextChar.toCodepoint()) {
                    case 'n': strValue += '\n'; break;
                    case 't': strValue += '\t'; break;
                    case 'r': strValue += '\r'; break;
                    case '\\': strValue += '\\'; break;
                    case '"': strValue += '"'; break;
                    default: strValue += nextChar; break;
                    }
                }
                else {
                    strValue += current;
                }
                position++;
            }
            if (current != '"') {
                auto _ = findLineAndColumn(source, position);
                stop({ INVALID_OR_UNEXPECTED_TOKEN, _.first, _.second, 1 });
            }
            position++;
            push(Token(TokenType::KEYWORD_STRING, strValue));
        }
        
        else
        {
            position++;
        }
    }
	return tokens;
}

void Lexer::stop(ErrorInfo info) {
    size_t line = info.x;
    size_t column = info.y;
    size_t length = info.length;
    column -= length;
    size_t currentLine = 1;
    size_t currentColumn = 1;
    std::string::size_type pos = 0;
    std::string::size_type lastPos = 0;
    String lineContent;

    while (currentLine < line && pos < source.length()) {
        if (source[pos] == '\n') {
            currentLine++;
        }
        pos++;
    }

    while (source[pos] != '\n' && pos < source.length()) {
        lineContent += source[pos];
        if (currentColumn + 1 == column) {
            lastPos = pos;
        }
        currentColumn++;
        pos++;
    }

    std::cout << lineContent << std::endl;

    std::string errorIndicator;
    for (int i = 1; i < column - 1; ++i) {
        errorIndicator += ' ';
    }
    for (int i = 0; i < length; ++i) {
        errorIndicator += '^';
    }
    std::cerr << errorIndicator << "\n\n"
        << "Uncaught SyntaxError: " << error_map[info.type] << std::endl;
    exit(-1);
}

void Lexer::push(expected<Token, ErrorInfo> t)
{
    if (!t)
    {
        stop(t.error());
    }
    tokens.emplace_back(t.value());
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
        auto _ = findLineAndColumn(source, position);
        return ErrorInfo{ INVALID_OR_UNEXPECTED_TOKEN, _.first, _.second, value.length() };
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
        auto _ = findLineAndColumn(source, position);
        return ErrorInfo{ INVALID_OR_UNEXPECTED_TOKEN, _.first, _.second, value.length() };
    }
    return Token{ TokenType::KEYWORD_DEC_NUMBER, value };
}

RETURN_AT_NEXT expected<Token, ErrorInfo> Lexer::getWord()
{
    String name;
    do
    {
        name += current;
        position++;
    } while (isWord());

    if (keywords.find(name) != keywords.end())
    {
        return Token{ keywords[name], name };
    }
    return Token{ TokenType::IDENTIFIER, name };
}

RETURN_AT_NEXT expected<Token, ErrorInfo> Lexer::getOperator() {
    String op;
    while (!std::isspace(current.toCodepoint())
            && !std::isalnum(current.toCodepoint()) && isOperatorStart()) {
        op += current;
        position++;
    }
    if (operatorMap.find(op) != operatorMap.end()) {
        return Token{ operatorMap[op], op };
    }
    else {
        auto _ = findLineAndColumn(source, position);
        return ErrorInfo{ INVALID_OR_UNEXPECTED_TOKEN, _.first, _.second, op.length() };
    }
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

bool Lexer::isWord(bool includeNumber)
{
    return (includeNumber ? std::isalnum(current.toCodepoint()) : std::isalpha(current.toCodepoint()))
        || (current == '_') || (current == '$');
}

bool Lexer::isOperatorStart() {
    switch (current.toCodepoint()) {
    case '+': case '-': case '*': case '/': case '=':
    case '|': case '~': case '!': case '%': case '^':
    case '&': case '?': case '<': case '>':
        return true;
    default:
        return false;
    }
}
