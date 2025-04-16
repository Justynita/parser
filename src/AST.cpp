#include "AST.h"
#include "Parser.h"

/*** Evaluating Visitor ***/

Value EvaluatingVisitor::evaluateExpression(ASTNode* node){

    /* visit the node based on its type */

    if(_M_is_tok_literal(node->token())){

        visitLiteralNode((LiteralNode*)node);
    }
    else if(_M_is_tok_binary(node->token())){

        visitBinaryNode((BinaryNode*)node);
    }
    else if(_M_is_tok_unary(node->token())){

        visitUnaryNode((UnaryNode*)node);
    }
    else {

        cerr << "Node is not literal, binary, or unary\n";
    }

    return _result;
}

void EvaluatingVisitor::visitBinaryNode(BinaryNode* node){

    Token tok = node->token();
    int tokType = tok.type();

    Value leftVal  = evaluateExpression(node->left());
    Value rightVal = evaluateExpression(node->right());

    int leftType = leftVal.type;
    int rightType = rightVal.type;

    // first check for strings

    /* Both operands are bools */
    if((leftType == VAL_BOOL) && (rightType == VAL_BOOL)){

        switch(tokType){
            // Comparison
            case _TOKEN_EQUAL_EQUAL:        { _result = _M_bool_val(_M_val_as_bool(leftVal) == _M_val_as_bool(rightVal)); break; }
            case _TOKEN_BANG_EQUAL:         { _result = _M_bool_val(_M_val_as_bool(leftVal) != _M_val_as_bool(rightVal)); break; }
            case _TOKEN_GREATER_EQUAL:      { _result = _M_bool_val(_M_val_as_bool(leftVal) >= _M_val_as_bool(rightVal)); break; }
            case _TOKEN_STRICTLY_GREATER:   { _result = _M_bool_val(_M_val_as_bool(leftVal) >  _M_val_as_bool(rightVal)); break; }
            case _TOKEN_LESS_EQUAL:         { _result = _M_bool_val(_M_val_as_bool(leftVal) <= _M_val_as_bool(rightVal)); break; }
            case _TOKEN_STRICTLY_LESS:      { _result = _M_bool_val(_M_val_as_bool(leftVal) <  _M_val_as_bool(rightVal)); break; }
            // Arithmetic
            case _TOKEN_BINOP_PLUS:         { _result = _M_num_val(_M_force_num(leftVal)    +  _M_force_num(rightVal)); break; }
            case _TOKEN_BINOP_MINUS:        { _result = _M_num_val(_M_force_num(leftVal)    -  _M_force_num(rightVal)); break; }     
            case _TOKEN_BINOP_MUL:          { _result = _M_num_val(_M_force_num(leftVal)    *  _M_force_num(rightVal)); break; }    
            case _TOKEN_BINOP_DIV:          { _result = _M_num_val(_M_force_num(leftVal)    /  _M_force_num(rightVal)); break; }     
        }
    }
    /* At least one operand is a number */
    else if((leftType == VAL_NUMBER) || (rightType == VAL_NUMBER))
    {
        switch(tokType){
            // Comparison
            case _TOKEN_EQUAL_EQUAL:        { _result = _M_bool_val(_M_force_num(leftVal) == _M_force_num(rightVal)); break; }
            case _TOKEN_BANG_EQUAL:         { _result = _M_bool_val(_M_force_num(leftVal) != _M_force_num(rightVal)); break; }
            case _TOKEN_GREATER_EQUAL:      { _result = _M_bool_val(_M_force_num(leftVal) >= _M_force_num(rightVal)); break; }
            case _TOKEN_STRICTLY_GREATER:   { _result = _M_bool_val(_M_force_num(leftVal) >  _M_force_num(rightVal)); break; }
            case _TOKEN_LESS_EQUAL:         { _result = _M_bool_val(_M_force_num(leftVal) <= _M_force_num(rightVal)); break; }
            case _TOKEN_STRICTLY_LESS:      { _result = _M_bool_val(_M_force_num(leftVal) < _M_force_num(rightVal)); break; }
            // Arithmetic
            case _TOKEN_BINOP_PLUS:     { _result = _M_num_val(_M_force_num(leftVal) +  _M_force_num(rightVal)); break; }
            case _TOKEN_BINOP_MINUS:    { _result = _M_num_val(_M_force_num(leftVal) -  _M_force_num(rightVal)); break; }     
            case _TOKEN_BINOP_MUL:      { _result = _M_num_val(_M_force_num(leftVal) *  _M_force_num(rightVal)); break; }    
            case _TOKEN_BINOP_DIV:      { _result = _M_num_val(_M_force_num(leftVal) /  _M_force_num(rightVal)); break; }     
        }
    }  
}

void EvaluatingVisitor::visitLiteralNode(LiteralNode* node){

    switch(node->token().type()){

        case _TOKEN_LITERAL_NUMBER: 
        { 
            _result = _M_num_val(stod(node->token().lexeme()));
            break; 
        }
        case _TOKEN_LITERAL_TRUE:   
        {
            _result = _M_bool_val(true);
            break; 
        } 
        case _TOKEN_LITERAL_FALSE:  
        {
            _result = _M_bool_val(false);
            break; 
        }
    }
}

void EvaluatingVisitor::visitUnaryNode(UnaryNode* node){
    /*
     * For '!' operator: treat 0 as false, any other number as true. 
     */

    Value rightVal = evaluateExpression(node->right());

    double right_num  = _M_is_val_num(rightVal)  ? _M_val_as_num(rightVal)  :  _M_bool_to_num(rightVal);

    switch(node->token().type()){

        case _TOKEN_UNARY_MINUS: { _result = _M_num_val((-1) * right_num);               break; }
        case _TOKEN_UNARY_BANG:  { _result = _M_bool_val(right_num == 0 ? true : false); break; }
    }
}

void EvaluatingVisitor::printResult(){

    cout << "\nResult: " + (_M_is_val_num(result()) ? to_string(_M_val_as_num(result())) : _M_bool_string(result())) + "\n";
}
    