#include <exception>
#include "AST.h"

#ifndef __H_PARSER
#define __H_PARSER

#define _M_is_tok_equality(token)                \
    (                                            \
    (token.type() == _TOKEN_EQUAL_EQUAL)      || \
    (token.type() == _TOKEN_BANG_EQUAL)          \
    )

#define _M_is_tok_comparison(token)              \
    (                                            \
    (token.type() == _TOKEN_GREATER_EQUAL)    || \
    (token.type() == _TOKEN_STRICTLY_GREATER) || \
    (token.type() == _TOKEN_LESS_EQUAL)       || \
    (token.type() == _TOKEN_STRICTLY_LESS)       \
    )                     

#define _M_is_tok_term(token)                    \
    (                                            \
    (token.type() == _TOKEN_BINOP_PLUS)       || \
    (token.type() == _TOKEN_BINOP_MINUS)         \
    )          

#define _M_is_tok_factor(token)                  \
    (                                            \
    (token.type() == _TOKEN_BINOP_MUL)        || \
    (token.type() == _TOKEN_BINOP_DIV)           \
    )          

#define _M_is_tok_logical(token)                 \
    (                                            \
    (token.type() == _TOKEN_LOGICAL_AND)      || \
    (token.type() == _TOKEN_LOGICAL_OR)          \
    )          

#define _M_is_tok_primary(token)                 \
    (                                            \
    (_M_is_tok_literal(token))                || \
    (token.type() == _TOKEN_OPEN_PARENTHESES) || \
    (token.type() == _TOKEN_CLOSE_PARENTHESES)   \
    )          

#define _M_tok_binding_power(token)              \
    (                                            \
    (_M_is_tok_unary(token)           ? 7 : 0) + \
    (_M_is_tok_factor(token)          ? 6 : 0) + \
    (_M_is_tok_term(token)            ? 5 : 0) + \
    (_M_is_tok_comparison(token)      ? 4 : 0) + \
    (_M_is_tok_equality(token)        ? 3 : 0) + \
    (_M_is_tok_logical(token)         ? 2 : 0) + \
    (_M_is_tok_primary(token)         ? 1 : 0)   \
    )


/*
*   statement   -> exprStmt 
*                | printStmt ;
*
*   exprStmt    -> expression ';' ;
*   printStmt   -> 'print' expression ';' ;
*
*   expression  -> logical ;
*   logical     -> equality (('and' | 'or') equality )* ;
*   equality    -> comparison (('!=' | '==') comparison )* ;
*   comparison  -> term (('>=' | '<=' | '>' | '<') term)* ;
*   term        -> factor (('+' | '-') factor)* ;
*   factor      -> unary (('*' | '/') unary)* ;
*   unary       -> ('!' | '-') unary 
*                | primary ;
*   primary     -> NUMBER | STRING | 'true' | 'false' 
*                | '(' expression ')' ;
*/


class Parser{

public:

    /* Constructor */
    Parser(tokenList &tokens): _tokens(tokens) {}

    /* getters */
    tokenList& tokens() { return _tokens; }

    /* actions */
    ASTNode* parse();
    ASTNode* recursiveParse(int &iterator, int rbp, ASTNode* left);

    ASTNode* createNode(int &iterator, int rbp, ASTNode* left);

private:
    tokenList &_tokens;

};


class ParsingException: public exception{

public:
    /* Constructor */
    ParsingException(const string& message): _message(message) {}

    /* throwing exception */
    virtual const char* what() const throw() { return _message.c_str(); }

private:
    string _message;

};

#endif