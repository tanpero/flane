#ifndef _COMPILER_TOKEN_HH_
#define _COMPILER_TOKEN_HH_

#include <string.hh>

enum class TokenType {
    // Keywords
    KEYWORD_IF,                 // if_statement
    KEYWORD_ELSE,
    KEYWORD_SWITCH,             // switch_statement
    KEYWORD_CASE,
    KEYWORD_DEFAULT,
    KEYWORD_WHILE,              // while_statement
    KEYWORD_FOR,                // for_statement
    KEYWORD_BREAK,              // break_statement
    KEYWORD_CONTINUE,           // continue_statement
    KEYWORD_RETURN,             // return_statement
    KEYWORD_EXPRESSION,         // expression_statement
    KEYWORD_LET_DECLARATION,    // let_declaration
    KEYWORD_CONST_DECLARATION,  // const_declaration
    KEYWORD_RANGE,              // range
    KEYWORD_MATCH,              // match_statement
    KEYWORD_STRING,                       // string
    KEYWORD_INTERPOLATION_STRING,         // interpolation_string
    KEYWORD_IDENTIFIER,                   // identifier
    KEYWORD_LITERAL,                      // literal
    KEYWORD_OBJECT_LITERAL,               // object_literal
    KEYWORD_PROPERTY_ASSIGNMENT,          // property_assignment
    KEYWORD_ARRAY_LITERAL,                // array_literal
    KEYWORD_ARROW_FUNCTION,               // arrow_function
    KEYWORD_ARROW_CASE,                   // arrow_case (in match)
    KEYWORD_NUMBER,                       // number
    KEYWORD_DEC_NUMBER,                   // dec_number
    KEYWORD_HEX_NUMBER,                   // hex_number
    KEYWORD_INTEGER,                      // integer
    KEYWORD_RATIO,                        // ratio

    // Operators
    OPERATOR_ADD,                     // +
    OPERATOR_SUBTRACT,                // -
    OPERATOR_MULTIPLY,                // *
    OPERATOR_DIVIDE,                  // /
    OPERATOR_MODULUS,                 // %
    OPERATOR_LEFT_SHIFT,              // <<
    OPERATOR_RIGHT_SHIFT,             // >>
    OPERATOR_ASSIGN,                  // =
    OPERATOR_ADD_ASSIGN,              // +=
    OPERATOR_SUBTRACT_ASSIGN,         // -=
    OPERATOR_MULTIPLY_ASSIGN,         // *=
    OPERATOR_DIVIDE_ASSIGN,           // /=
    OPERATOR_MODULUS_ASSIGN,          // %=
    OPERATOR_LEFT_SHIFT_ASSIGN,       // <<=
    OPERATOR_RIGHT_SHIFT_ASSIGN,      // >>=
    OPERATOR_EQUALS,                  // ==
    OPERATOR_NOT_EQUALS,              // !=
    OPERATOR_LESS_THAN,               // <
    OPERATOR_GREATER_THAN,            // >
    OPERATOR_LESS_THAN_OR_EQUAL,      // <=
    OPERATOR_GREATER_THAN_OR_EQUAL,   // >=
    OPERATOR_EXPONENT,                // **
    OPERATOR_LOGICAL_AND,
    OPERATOR_LOGICAL_OR,
    OPERATOR_LOGICAL_NOT,
    OPERATOR_BITWISE_AND,
    OPERATOR_BITWISE_OR,
    OPERATOR_BITWISE_XOR,
    OPERATOR_BITWISE_NOT,
    OPERATOR_QUESTION, 
    OPERATOR_COLON,

    // Delimiters
    DELIMITER_OPEN_PARENTHESIS,       // (
    DELIMITER_CLOSE_PARENTHESIS,      // )
    DELIMITER_OPEN_BRACE,             // {
    DELIMITER_CLOSE_BRACE,            // }
    DELIMITER_OPEN_BRACKET,           // [
    DELIMITER_CLOSE_BRACKET,          // ]
    DELIMITER_COMMA,                  // ,
    DELIMITER_COLON,                  // :

    // Literals
    LITERAL_TRUE,                   // true
    LITERAL_FALSE,                  // false
    LITERAL_NONE,                   // none

    // Identifiers
    IDENTIFIER,                     // Identifier

    // Special
    EOF_TOKEN,                      // End of File Token
    UNKNOWN,
};

struct Token
{
    TokenType type;
    String value;

    Token(TokenType type, String value) : type(type), value(value) {}

    String toString() const;
    bool is(TokenType t) const;
};


#endif // !_COMPILER_TOKEN_HH_
