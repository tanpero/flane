#ifndef _COMPILER_TOKEN_HH_
#define _COMPILER_TOKEN_HH_

#include <string.hh>

enum class TokenType {
    // Keywords
    KEYWORD_IF_STATEMENT,                 // if_statement
    KEYWORD_SWITCH_STATEMENT,             // switch_statement
    KEYWORD_WHILE_STATEMENT,              // while_statement
    KEYWORD_FOR_STATEMENT,                // for_statement
    KEYWORD_BREAK_STATEMENT,              // break_statement
    KEYWORD_CONTINUE_STATEMENT,           // continue_statement
    KEYWORD_RETURN_STATEMENT,             // return_statement
    KEYWORD_EXPRESSION_STATEMENT,         // expression_statement
    KEYWORD_LET_DECLARATION,              // let_declaration
    KEYWORD_CONST_DECLARATION,            // const_declaration
    KEYWORD_FOR,                          // for
    KEYWORD_RANGE,                        // range
    KEYWORD_MATCH_STATEMENT,              // match_statement
    KEYWORD_STRING,                       // string
    KEYWORD_INTERPOLATION_STRING,         // interpolation_string
    KEYWORD_IDENTIFIER,                   // identifier
    KEYWORD_LITERAL,                      // literal
    KEYWORD_OBJECT_LITERAL,               // object_literal
    KEYWORD_PROPERTY_ASSIGNMENT,          // property_assignment
    KEYWORD_ARRAY_LITERAL,                // array_literal
    KEYWORD_ARROW_FUNCTION,               // arrow_function
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
