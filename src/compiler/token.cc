#include <token.hh>

String Token::toString() const {
    return value;
}

bool Token::is(TokenType t) const {
    return type == t;
}
