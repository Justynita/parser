#include "./lexer/Lexer.h"
#include "Value.h"

#ifndef __H_AST
#define __H_AST

using namespace std;

class ASTNode;
class BinaryNode;
class LiteralNode;
class UnaryNode;

/**************
 *  Visitors  *
 **************/

class NodeVisitor{

public:
    /* visiting functions */
    virtual void visitBinaryNode(BinaryNode*) = 0;
    virtual void visitLiteralNode(LiteralNode*) = 0;
    virtual void visitUnaryNode(UnaryNode*) = 0;

    /* Destructor */
    virtual ~NodeVisitor() {}

protected:
    NodeVisitor() {}
};

/* Visitor for evaluating the result */

class EvaluatingVisitor : public NodeVisitor{

public:
    /* evaluate */
    Value evaluateExpression(ASTNode* node);
    void printResult();

    Value result() { return _result; }

    /* visiting functions */
    virtual void visitBinaryNode(BinaryNode* node);
    virtual void visitLiteralNode(LiteralNode* node);
    virtual void visitUnaryNode(UnaryNode* node);

private:
    Value _result;
};


/***********
 *  Nodes  *
 ***********/

class ASTNode{

public:
    /* getters */
    const Token token() { return _token; }

    /* acceptor */
    virtual void accept(NodeVisitor&) = 0;

    /* Destructor */
    virtual ~ASTNode() {}

protected:
    ASTNode(Token token) : _token(token) {}

private:
    Token _token;
};


/* Binary Node */

class BinaryNode : public ASTNode{

public:
    /* Constructor */
    BinaryNode(Token token, ASTNode* left, ASTNode* right) : ASTNode(token), _left(left), _right(right) {}

    /* getters */
    ASTNode* left()  { return _left; }
    ASTNode* right() { return _right; }

    /* acceptor */
    virtual void accept(NodeVisitor& v) { v.visitBinaryNode(this); }

private:

    ASTNode* _left;
    ASTNode* _right;

};

/* Literal Node */

class LiteralNode : public ASTNode{

public:
    /* Constructor */
    LiteralNode(Token token) : ASTNode(token) {}

    /* acceptor */
    virtual void accept(NodeVisitor& v) { v.visitLiteralNode(this); }
};

/* Unary Node */

class UnaryNode : public ASTNode{

public:
    /* Constructor */
    UnaryNode(Token token, ASTNode* right) : ASTNode(token), _right(right) {}

    /* getters */
    ASTNode* right() { return _right; }

    /* acceptor */
    virtual void accept(NodeVisitor& v) { v.visitUnaryNode(this); }

private:
    ASTNode* _right;

};


#endif