#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <set>
#include <vector>
#include "lexer.h"

using namespace std;

class parser
{
private:
    LexicalAnalyzer lexer;

    void syntax_error();
    Token expect(TokenType expected_type);
    Token peek();
    Token peek_ahead();

    TokenType getTypeOfID(string id);
    bool isVariableDeclared(string id);
    int initializeID(string id);
    bool isVariableInitialized(string id);
    bool isVariableInitializedInCurentScope(string id);
    bool variableAlreadyInCurrentScope(string varName);


    void errorCode1_1(string variable);
    void errorCode1_2(string variable);
    void errorCode1_3(string variable);
    void typeMisMatch_C1(Token t);
    void typeMisMatch_C2(Token t);
    void typeMisMatch_C3(Token t);
    void typeMisMatch_C4(Token t);
    void typeMisMatch_C5(Token t);
    void typeMisMatch_C6(Token t);
    void typeMisMatch_C7(Token t);

    int getDeclarationLineNumber(string id);
    void feedIntoUniversalDeclaredVariable(string id, int line_num);
    void feedIntoFinalOutput(string id, int ref_line_no, int decl_line_no);
    bool isThereAnyUnusedVariable();
    bool isThereAnyUnusedVariableInCurrentScope();

    void parse_scope();
    void parse_scope_list();
    void parse_var_decl();
    void parse_stmt();
    void parse_id_list();
    void parse_type_name();
    void parse_stmt_list();
    void parse_assign_stmt();
    void parse_while_stmt();
    TokenType parse_expr();
    void parse_arithmetic_operator();
    void parse_binary_boolean_operator();
    void parse_relational_operator();
    TokenType parse_primary();
    void parse_bool_const();
    void parse_condition();


public:
    void parse_program();
};

#endif //PARSER_H
