#ifndef _COMPILER_LEXER_HH_
#define _COMPILER_LEXER_HH_

#include <token.hh>
#include <expected>

class Lexer {
	String source;
	size_t position;
	size_t readPosition;
	std::vector<Token> tokens;

	size_t deepOfInterpolation;

public:
	Lexer(const String& source)
		: source(source),
		position(0),
		readPosition(0),
		tokens({}),
		deepOfInterpolation(0)
	{}

	std::vector<Token> tokenize();

	void skipBlank();

private:
	bool isBlank();
};



#endif // !_COMPILER_LEXER_HH_
