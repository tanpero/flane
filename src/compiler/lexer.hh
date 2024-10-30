#ifndef _COMPILER_LEXER_HH_
#define _COMPILER_LEXER_HH_

#include <token.hh>
#include <expected.hh>
#include <error.hh>

class Lexer {
	String source;
	size_t position;
	size_t readPosition;
	std::vector<Token> tokens;

	size_t deepOfInterpolation;

	size_t x, y;

public:
	Lexer(const String& source)
		: source(source),
		position(0),
		readPosition(0),
		tokens({}),
		deepOfInterpolation(0),
		x(0), y(0)
	{}

	std::vector<Token> tokenize();
	void stop(ErrorInfo info);

	void skipBlank();
	expected<Token, ErrorInfo> getDecNumber();
	expected<Token, ErrorInfo> getHexNumber();

private:
	bool isBlank();
};



#endif // !_COMPILER_LEXER_HH_
