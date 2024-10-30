#include <lexer.hh>

static void expect(Char c, Char exp, size_t offset) {
    if (c != exp) {
        std::cerr << "Invalid Character: \"" << c << "\" at position " << offset
            << ", it should be \"" << exp << "\"." << std::endl;
        exit(-1);
    }
}

static void expect(Char c, bool ok, String exp, size_t offset) {
    if (!ok) {
        std::cerr << "Invalid Character: \"" << c << "\" at position " << offset
            << ", it should be " << exp << "." << std::endl;
        exit(-1);
    }
}

std::vector<Token> Lexer::tokenize()
{
    while (position < source.length()) {
        Char c = source[position];
        position++;
    }
	return std::vector<Token>();
}

void Lexer::skipBlank()
{
    while (isBlank())
    {
        position++;
    }
}

bool Lexer::isBlank()
{
    switch (source[position].toCodepoint())
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
