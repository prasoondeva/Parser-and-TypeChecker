#include <iostream>
#include <cstdlib>
#include<cstring>
#include<string>
#include "lexer.h"
#include "parser.h"

using namespace std;

Token t;
LexicalAnalyzer lexer;
vector<string> unInitializedVariableErrors;

struct Scope
{
    vector<string> idList;
    vector<TokenType> typeList;
    vector<int> initializedIDList;
    struct Scope* parent;
};

struct DeclaredVariable
{
    string id;
    int declaration_line_no;
};

struct VariableName_ReferenceLine_DeclarationLine
{
    string id;
    int reference_line_no;
    int declaration_line_no;
};

vector<DeclaredVariable> universalDeclaredVariableList;
vector<VariableName_ReferenceLine_DeclarationLine> finalOutput;

Scope* currentScope;

void parser::syntax_error()
{
    cout << "Syntax Error\n";
    exit(1);
}

Token parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

Token parser::peek()
{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

Token parser::peek_ahead()
{
    Token t = lexer.GetToken();
    Token t1 = lexer.GetToken();
    lexer.UngetToken(t1);
    lexer.UngetToken(t);
    return t1;
}

TokenType parser::getTypeOfID(string id)
{
    Scope* s = currentScope;
    while(s != NULL)
    {
        int index = 0;
        for(auto i : s->idList)
        {
            if(i == id)
            {
                return s->typeList[index];
            }
            else
            {
                index++;
            }
        }
        s = s->parent;
    }
}

bool parser::isVariableDeclared(string id)
{
    bool isVariableDeclared = false;
    Scope* s = currentScope;
    while(s != NULL)
    {
        for(auto i : s->idList)
        {
            if(i == id)
            {
                isVariableDeclared = true;
                return isVariableDeclared;
            }
        }
        s = s->parent;
    }
    return isVariableDeclared;
}

int parser::initializeID(string id)
{
    Scope* s = currentScope;
    while(s != NULL)
    {
        int index = 0;
        for(auto i : s->idList)
        {
            if(i == id)
            {
                s->initializedIDList[index] = 1;
                return 0;
            }
            else
            {
                index++;
            }
        }
        s = s->parent;
    }
}

bool parser::isVariableInitialized(string id)
{
    bool isVariableInitialized = false;
    Scope* s = currentScope;
    int index = 0;
    while(s != NULL)
    {
        for(auto i : s->idList)
        {
            if(i == id)
            {
                if(s->initializedIDList[index] == 1)
                {
                    isVariableInitialized = true;
                    return isVariableInitialized;
                }
            }
            else
            {
                index++;
            }
        }
        s = s->parent;
        index = 0;
    }
    return isVariableInitialized;
}

bool parser::variableAlreadyInCurrentScope(string varName)
{
    bool variableAlreadyInCurrentScope = false;
    for(auto i : currentScope->idList)
    {
        if(i == varName)
        {
            variableAlreadyInCurrentScope = true;
            break;
        }
    }
    return variableAlreadyInCurrentScope;
}

void parser::errorCode1_1(string variable)
{
    cout << "ERROR CODE 1.1 " + variable;
    exit(1);
}

void parser::errorCode1_2(string variable)
{
    cout << "ERROR CODE 1.2 " + variable;
    exit(1);
}

void parser::errorCode1_3(string variable)
{
    cout << "ERROR CODE 1.3 " + variable;
    exit(1);
}

void parser::typeMisMatch_C1(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C1" << endl;
    exit(1);
}

void parser::typeMisMatch_C2(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C2" << endl;
    exit(1);
}

void parser::typeMisMatch_C3(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C3" << endl;
    exit(1);
}

void parser::typeMisMatch_C4(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C4" << endl;
    exit(1);
}

void parser::typeMisMatch_C5(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C5" << endl;
    exit(1);
}

void parser::typeMisMatch_C6(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C6" << endl;
    exit(1);
}

void parser::typeMisMatch_C7(Token t)
{
    cout << "TYPE MISMATCH " << t.line_no << " C7" << endl;
    exit(1);
}

int parser::getDeclarationLineNumber(string id)
{
    for(int i = universalDeclaredVariableList.size()-1; i >= 0; i--)
    {
        if(universalDeclaredVariableList[i].id == id)
        {
            return universalDeclaredVariableList[i].declaration_line_no;
        }
    }
}

void parser::feedIntoUniversalDeclaredVariable(string id, int line_num)
{
    DeclaredVariable nameDecl;
    nameDecl.id = id;
    nameDecl.declaration_line_no = line_num;
    universalDeclaredVariableList.push_back(nameDecl);
}

void parser::feedIntoFinalOutput(string id, int ref_line_no, int decl_line_no)
{
    VariableName_ReferenceLine_DeclarationLine nameRefDecl;
    nameRefDecl.id = id;
    nameRefDecl.reference_line_no = ref_line_no;
    nameRefDecl.declaration_line_no = decl_line_no;
    finalOutput.push_back(nameRefDecl);
}

bool parser::isThereAnyUnusedVariable()
{
    for(auto i : universalDeclaredVariableList)
    {
        bool elementFound = false;
        for(auto j : finalOutput)
        {
            if(i.id == j.id)
            {
                elementFound = true;
                break;
            }
        }
        if(!elementFound)
        {
            errorCode1_3(i.id);
        }
    }
    return false;
}

int idListVariableCount = 0;
void parser::parse_id_list()
{
    //id_list -> ID COMMA id_list
    //id_list -> ID
    Token t1 = peek();
    Token t2 = peek_ahead();

    if(t1.token_type == ID && t2.token_type == COMMA)
    {
        Token t = expect(ID);
        //Check for error code 1.4
        if(t.lexeme != "REAL" || t.lexeme != "INT" || t.lexeme != "BOOLEAN" || t.lexeme != "STRING")
        {
            if(!variableAlreadyInCurrentScope(t.lexeme))
            {
                currentScope->idList.push_back(t.lexeme);
                currentScope->initializedIDList.push_back(0);

                feedIntoUniversalDeclaredVariable(t.lexeme, t.line_no);

                idListVariableCount++;
            }
            else
            {
                errorCode1_1(t.lexeme);
            }
        }
        else
        {
            syntax_error();
        }
        expect(COMMA);
        parse_id_list();
    }
    else if(t1.token_type == ID )
    {
        Token t = expect(ID);
        Token t_type = peek_ahead();
        //Check for error code 1.4
        if(t.lexeme != "REAL" || t.lexeme != "INT" || t.lexeme != "BOOLEAN" || t.lexeme != "STRING")
        {
            //For id_list -> ID
            if(!variableAlreadyInCurrentScope(t.lexeme) && idListVariableCount == 0)
            {
                currentScope->idList.push_back(t.lexeme);
                currentScope->typeList.push_back(t_type.token_type);
                currentScope->initializedIDList.push_back(0);

                feedIntoUniversalDeclaredVariable(t.lexeme, t.line_no);
            }
            //For id_list -> ID id_list
            //In this case last element of list will be a single id and idListVariableCount is not 0, so we came to this else if block
            else if(!variableAlreadyInCurrentScope(t.lexeme) && idListVariableCount != 0)
            {
                currentScope->idList.push_back(t.lexeme);
                currentScope->initializedIDList.push_back(0);

                feedIntoUniversalDeclaredVariable(t.lexeme, t.line_no);

                idListVariableCount++;
                for(int i = 0; i < idListVariableCount; i++)
                {
                    currentScope->typeList.push_back(t_type.token_type);
                }
                idListVariableCount = 0;
            }
            else
            {
                errorCode1_1(t.lexeme);
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_type_name()
{
    //type_name -> REAL
    //type_name -> INT
    //type_name -> BOOLEAN
    //type_name -> STRING
    Token t = peek();

    if(t.token_type == REAL)
    {
        Token t = expect(REAL);
    }
    else if(t.token_type == INT)
    {
        Token t = expect(INT);
    }
    else if(t.token_type == BOOLEAN)
    {
        Token t = expect(BOOLEAN);
    }
    else if(t.token_type == STRING)
    {
        Token t = expect(STRING);
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_var_decl()
{
    //var_decl -> id_list COLON type_name SEMICOLON
    parse_id_list();
    expect(COLON);
    parse_type_name();
    expect(SEMICOLON);
}

void parser::parse_bool_const()
{
    //bool_const -> TRUE | FALSE
    Token t = peek();

    if(t.token_type == TRUE)
    {
        expect(TRUE);
    }
    else if(t.token_type == FALSE)
    {
        expect(FALSE);
    }
    else
    {
        syntax_error();
    }
}

TokenType parser::parse_primary()
{
    //primary -> ID | NUM | REALNUM | STRING_CONSTANT | bool_const
    Token t = peek();

    if(t.token_type == ID)
    {
        Token t = expect(ID);
        if(isVariableDeclared(t.lexeme))
        {
            feedIntoFinalOutput(t.lexeme,t.line_no,getDeclarationLineNumber(t.lexeme));
            if(isVariableInitialized(t.lexeme))
            {
                return getTypeOfID(t.lexeme);
            }
            else
            {
                unInitializedVariableErrors.push_back("UNINITIALIZED " + t.lexeme + " " +to_string(t.line_no));
                return getTypeOfID(t.lexeme);
            }
        }
        else
        {
            errorCode1_2(t.lexeme);
        }
    }
    else if(t.token_type == NUM)
    {
        expect(NUM);
        return(INT);
    }
    else if(t.token_type == REALNUM)
    {
        expect(REALNUM);
        return(REAL);
    }
    else if(t.token_type == STRING_CONSTANT)
    {
        expect(STRING_CONSTANT);
        return(STRING);
    }
    else if(t.token_type == TRUE || t.token_type == FALSE )
    {
        parse_bool_const();
        return(BOOLEAN);
    }
    else
    {
        syntax_error();
    }

}

void parser::parse_relational_operator()
{
    //relational operator -> GREATER | GTEQ | LESS | NOTEQUAL | LTEQ
    Token t = peek();

    if(t.token_type == GREATER)
    {
        expect(GREATER);
    }
    else if(t.token_type == GTEQ)
    {
        expect(GTEQ);
    }
    else if(t.token_type == LESS)
    {
        expect(LESS);
    }
    else if(t.token_type == NOTEQUAL)
    {
        expect(NOTEQUAL);
    }
    else if(t.token_type == LTEQ)
    {
        expect(LTEQ);
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_binary_boolean_operator()
{
    //binary boolean operator -> AND | OR | XOR
    Token t = peek();

    if(t.token_type == AND)
    {
        expect(AND);
    }
    else if(t.token_type == OR)
    {
        expect(OR);
    }
    else if(t.token_type == XOR)
    {
        expect(XOR);
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_arithmetic_operator()
{
    //arithmetic operator -> PLUS | MINUS | MULT | DIV
    Token t = peek();

    if(t.token_type == PLUS)
    {
        expect(PLUS);
    }
    else if(t.token_type == MINUS)
    {
        expect(MINUS);
    }
    else if(t.token_type == MULT)
    {
        expect(MULT);
    }
    else if(t.token_type == DIV)
    {
        expect(DIV);
    }
    else
    {
        syntax_error();
    }
}

TokenType parser::parse_expr()
{
    //expr -> arithmetic operator expr expr
    //expr -> binary boolean operator expr expr
    //expr -> relational operator expr expr
    //expr -> NOT expr
    //expr -> primary
    Token t = peek();

    if( t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV)
    {
        parse_arithmetic_operator();
        TokenType type1 = parse_expr();
        TokenType type2 = parse_expr();
        if((type1 == INT || type1 == REAL) && (type2 == INT || type2 == REAL))
        {
            //Implementing I2
            if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT)
            {
                if(type1 == INT || type2 == INT)
                {
                    return INT;
                }
                else
                {
                    return REAL;
                }
            }
            //Implementing I3
            else if(t.token_type == DIV)
            {
                if(type1 == INT || type2 == INT)
                {
                    return REAL;
                }
                else
                {
                    return REAL;
                }
            }
        }
        else
        {
            typeMisMatch_C3(t);
        }
    }
    else if  (t.token_type == AND || t.token_type == OR || t.token_type == XOR)
    {
        parse_binary_boolean_operator();
        TokenType type1 = parse_expr();
        TokenType type2 = parse_expr();
        if(type1 == BOOLEAN && type2 == BOOLEAN)
        {
            return BOOLEAN;
        }
        else
        {
            typeMisMatch_C4(t);
        }
    }
    else if ( t.token_type == GREATER || t.token_type == GTEQ || t.token_type == LESS || t.token_type == NOTEQUAL || t.token_type == LTEQ)
    {
        parse_relational_operator();
        TokenType type1 = parse_expr();
        TokenType type2 = parse_expr();
        if(!(type1 == INT || type1 == REAL) && !(type2 == INT || type2 == REAL))
        {
            if(type1 == STRING && type2 == STRING)
            {
                return BOOLEAN;
            }
            else if(type1 == BOOLEAN && type2 == BOOLEAN)
            {
                return BOOLEAN;
            }
            else
            {
                typeMisMatch_C5(t);
            }
        }
        else if(type1 == INT || type1 == REAL)
        {
            if(type2 == INT || type2 == REAL)
            {
                return BOOLEAN;
            }
            else
            {
                typeMisMatch_C6(t);
            }
        }
        else if(type2 == INT || type2 == REAL)
        {
            if(type1 == INT || type1 == REAL)
            {
                return BOOLEAN;
            }
            else
            {
                typeMisMatch_C6(t);
            }
        }
    }
    else if ( t.token_type == ID || t.token_type == NUM || t.token_type == REALNUM || t.token_type == STRING_CONSTANT || t.token_type == TRUE || t.token_type == FALSE)
    {
        TokenType type = parse_primary();
        return type;
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_assign_stmt()
{
    //assign_stmt -> ID EQUAL expr SEMICOLON
    Token t1 = expect(ID);
    if(isVariableDeclared(t1.lexeme))
    {
        feedIntoFinalOutput(t1.lexeme,t1.line_no,getDeclarationLineNumber(t1.lexeme));

        TokenType type1 = getTypeOfID(t1.lexeme);

        expect(EQUAL);

        TokenType type2 = parse_expr();
        if(type1 == INT && type2 == INT)
        {
            expect(SEMICOLON);
            initializeID(t1.lexeme);
        }
        else if(type1 == STRING && type2 == STRING)
        {
            expect(SEMICOLON);
            initializeID(t1.lexeme);
        }
        else if(type1 == BOOLEAN && type2 == BOOLEAN)
        {
            expect(SEMICOLON);
            initializeID(t1.lexeme);
        }
        else if(type1 == REAL)
        {
            if(type2 == REAL || type2 == INT)
            {
                expect(SEMICOLON);
                initializeID(t1.lexeme);
            }
            else
            {
                typeMisMatch_C2(t1);
            }
        }
        else
        {
            typeMisMatch_C1(t1);
        }
    }
    else
    {
        errorCode1_2(t1.lexeme);
    }
}

void parser::parse_condition()
{
    //condition -> LPAREN expr RPAREN
    Token t = expect(LPAREN);
    TokenType type = parse_expr();
    if(type == BOOLEAN)
    {
        expect(RPAREN);
    }
    else
    {
        typeMisMatch_C7(t);
    }
}

void parser::parse_stmt()
{
    //stmt -> assign stmt
    //stmt -> while stmt
    Token t = peek();

    if(t.token_type == ID)
    {
        parse_assign_stmt();
    }
    else if(t.token_type == WHILE)
    {
       parse_while_stmt();
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_stmt_list()
{
    //stmt_list -> stmt
    //stmt_list -> stmt stmt_list
    parse_stmt();

    Token t = peek();

    if(t.token_type == ID || t.token_type == WHILE)
    {
        parse_stmt_list();
    }
    else if(t.token_type == RBRACE)
    {

    }
    else
    {
        syntax_error();
    }
}

void parser::parse_while_stmt()
{
    //while_stmt -> WHILE condition LBRACE stmt_list RBRACE
    //while_stmt -> WHILE condition stmt
    expect(WHILE);
    parse_condition();

    Token t = peek();

    if(t.token_type == LBRACE)
    {
        expect(LBRACE);
        parse_stmt_list();
        expect(RBRACE);
    }
    else if(t.token_type == ID || t.token_type == WHILE )
    {
        parse_stmt();
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_scope_list()
{
    Token t1 = peek();
    Token t2 = peek_ahead();

    //scope_list -> var_decl
    if((t1.token_type == ID && t2.token_type == COLON) ||(t1.token_type == ID && t2.token_type == COMMA))
    {
        parse_var_decl();
        Token t1 = peek();
        if(t1.token_type == ID || t1.token_type == LBRACE || t1.token_type == WHILE)
        {
            //scope_list -> var_decl scope_list
            parse_scope_list();
        }
    }
    //scope_list -> stmt
    else if ((t1.token_type == ID && t2.token_type == EQUAL) ||(t1.token_type == WHILE))
    {
        parse_stmt();
        Token t1 = peek();
        if(t1.token_type == ID || t1.token_type == LBRACE || t1.token_type == WHILE )
        {
            //scope_list -> stmt scope_list
            parse_scope_list();
        }
    }
    // scope_list -> scope
    else if(t1.token_type == LBRACE)
    {
        parse_scope();
        Token t1 = peek();
        if(t1.token_type == ID || t1.token_type == LBRACE || t1.token_type == WHILE)
        {
            //scope_list -> scope scope_list
            parse_scope_list();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::parse_scope()
{
    expect(LBRACE);

    Scope* parent = currentScope;
    currentScope = new Scope;
    currentScope->parent = parent;

    parse_scope_list();
    expect(RBRACE);

    Scope *tempScope = currentScope;
    currentScope = currentScope->parent;
    free(tempScope);
}

void parser::parse_program()
{
    parse_scope();
    Token t = lexer.GetToken();
    if(t.token_type != END_OF_FILE)
    {
        syntax_error();
    }
    else
    {
        if(unInitializedVariableErrors.size() != 0)
        {
            for(auto i : unInitializedVariableErrors)
            {
                cout << i << endl;
            }
        }
        else if(!isThereAnyUnusedVariable())
        {
            for(auto i : finalOutput)
            {
                cout << i.id << " " << i.reference_line_no << " " << i.declaration_line_no << endl;
            }
        }
    }
}

int main()
{
    parser p;
    p.parse_program();

    return 0;
}
