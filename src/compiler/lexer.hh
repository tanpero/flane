#ifndef _COMPILER_LEXER_HH_
#define _COMPILER_LEXER_HH_

#include <map>
#include <set>
#include <token.hh>
#include <expected.hh>
#include <error.hh>

#define RETURN_AT_TAIL /* When the function returns, position will be at the last character of token */
#define RETURN_AT_NEXT /* When the function returns, position will be at the first character after token */

class Lexer {
	String source;
	size_t position;
	size_t readPosition;
	std::vector<Token> tokens;

	size_t deepOfInterpolation;
	bool isCurrentCharContainedOfString;

	String stringContent;

public:
	Lexer(const String& source)
		: source(source),
		position(0),
		readPosition(0),
		tokens({}),
		deepOfInterpolation(0),
		isCurrentCharContainedOfString(false),
		stringContent("")
	{}

	std::vector<Token> tokenize();
	void stop(ErrorInfo info);
	void push(expected<Token, ErrorInfo> t);

	void skipBlank();
	RETURN_AT_NEXT expected<Token, ErrorInfo> getDecNumber();
	RETURN_AT_NEXT expected<Token, ErrorInfo> getHexNumber();
	RETURN_AT_NEXT expected<Token, ErrorInfo> getWord();
	RETURN_AT_NEXT expected<Token, ErrorInfo> getOperator();
	RETURN_AT_TAIL void tokenizeTemplateString();

private:
	bool isBlank();
	bool isWord(bool includeNumber = true);
	bool isOperatorStart();
	void pushStringToken(const String& strValue);
};



#endif // !_COMPILER_LEXER_HH_
