#ifndef _COMPILER_TOKEN_HH_
#define _COMPILER_TOKEN_HH_

enum Token {
    // �ؼ���
    IF, ELSE, SWITCH, CASE, DEFAULT, WHILE, FOR, BREAK, CONTINUE, LET, CONST, TRUE, FALSE, NULL, UNDEFINED,

    // ������
    ASSIGN, PLUS_ASSIGN, MINUS_ASSIGN, MUL_ASSIGN, DIV_ASSIGN, EXP_ASSIGN, MOD_ASSIGN,
    LOGICAL_OR, LOGICAL_AND,
    EQUAL, NOT_EQUAL,
    LESS_THAN, GREATER_THAN, LESS_EQUAL, GREATER_EQUAL,
    ADD, SUB,
    MUL, DIV, MOD,
    EXP,

    // һԪ������
    PLUS, MINUS, NOT,

    // �ָ���
    SEMICOLON, COMMA,

    // ����
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,

    // ������
    IDENTIFIER, STRING_LITERAL, NUMBER_LITERAL,

    // ����
    ARROW_FUNCTION,

    // ����
    EOF // ��ʾ�ļ�����
};

#endif // !_COMPILER_TOKEN_HH_
