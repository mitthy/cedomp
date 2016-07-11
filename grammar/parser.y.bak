%{
    #include <string>
    #include <vector>
    #include <map>
    #include <iostream>
    #include "Semantic/VarAssign.h"
    #include "AST/AST.h"
    #include "Exceptions/CedompException.h"
    extern int yylex();
    extern int yyparse();
    extern void yyerror(const char* s, ...);
    using std::cout;
    using std::endl;

%}



%union {
    double* floattype;
    long* inttype;
    std::string* strtype;
    std::vector<void*>* listtype;
    std::map<std::string, void*>* maptype;
    char* id;
    std::vector<Cedomp::Semantic::VarNameIndex>* typevarlist;
    std::vector<Cedomp::AST::ExpressionNode*>* typeassignlist;
    std::vector<Cedomp::AST::AssignVariableNode*>* typevarassign;
    Cedomp::AST::ExpressionNode* typeexpr;
}

%token T_NL
%token T_SEMICOLON T_COMMA T_LEFT_PAR T_RIGHT_PAR T_LEFT_BRACKET T_RIGHT_BRACKET  T_ASSIGN T_COLON
%token T_MAP T_LIST T_TRUE T_FALSE T_STRING T_ID T_INT T_FLOAT
%token T_DEF T_END T_RETURN T_FOR T_IF T_ELSE
%token T_AND T_XOR T_OR T_MOD T_NOT T_EQUALS T_DIFFERENT T_GREATER_EQUAL T_LESS_EQUAL T_GREATER T_LESS T_PLUS T_STAR T_SLASH T_MINUS

%type<typeexpr> expr
%type<typevarlist> varlist
%type<typeassignlist> assignlist
%type<typevarassign> varassign
%type<strtype> T_STRING
%type<inttype> T_INT
%type<id> T_ID
%type<floattype> T_FLOAT
%type<maptype> T_MAP
%type<listtype> T_LIST

%left T_EQUALS T_DIFFERENT T_GREATER_EQUAL T_LESS_EQUAL T_GREATER T_LESS
%left T_AND
%left T_OR
%left T_XOR
%left T_NOT
%left T_MOD
%left T_PLUS T_MINUS
%left T_STAR T_SLASH
%left UNARY_MINUS


%%

head:
statements
{
}
;

statements:
statements statement T_NL
{
}
|
statement T_NL
{
}
|
T_NL
{
}
|
statements T_NL
{
}
|
error T_NL
{
}
;

statement:
declfun
{
}
|
expr
{
}
|
ifstat
{
}
|
forstat
{
}
|
T_RETURN expr
{
}
|
varassign
{
}
;

forstat:
T_FOR T_LEFT_PAR for_init T_SEMICOLON for_cond T_SEMICOLON for_expr T_RIGHT_PAR T_COLON T_NL for_body T_END
{
}
;

for_init:
expr
{
}
|
%empty
{
}
;

for_cond:
expr
{
}
|
%empty
{
}
;

for_expr:
expr
{
}
|
%empty
{
}
;

for_body:
statements
{
}
;

ifstat:
T_IF expr T_COLON T_NL statements T_END
{
}
|
T_IF expr T_COLON T_NL statements T_ELSE T_COLON T_NL statements T_END
{
}
;

declfun:
T_DEF T_ID T_LEFT_PAR arglist T_RIGHT_PAR T_COLON T_NL declfuntail
{
}
|
T_DEF T_ID T_LEFT_PAR T_RIGHT_PAR T_COLON T_NL declfuntail
{
}
;

arglist:
arglist T_COMMA expr
{
}
|
expr
{
}
;

declfuntail:
funcbody T_END
{
}
;

funcbody:
statements
{
}
|
%empty
{
}
;

expr:
T_ID
{
}
|
T_INT
{
}
|
T_FLOAT
{
}
|
T_STRING
{
}
|
T_MAP T_LEFT_PAR T_RIGHT_PAR
{
}
|
T_LIST T_LEFT_PAR T_RIGHT_PAR
{
}
|
T_ID T_LEFT_BRACKET expr T_RIGHT_BRACKET
{
}
|
expr T_MOD expr
{
}
|
expr T_PLUS expr
{
}
|
expr T_MINUS expr
{
}
|
expr T_STAR expr
{
}
|
expr T_SLASH expr
{
}
|
T_MINUS expr %prec UNARY_MINUS
{
}
|
expr T_GREATER expr
{
}
|
expr T_EQUALS expr
{
}
|
expr T_GREATER_EQUAL expr
{
}
|
T_TRUE
{
}
|
T_FALSE
{
}
|
expr T_AND expr
{
}
|
expr T_XOR expr
{
}
|
expr T_OR expr 
{
}
|
T_NOT expr 
{
}
|
expr T_DIFFERENT expr
{
}
|
expr T_LESS_EQUAL expr 
{
}
|
expr T_LESS expr
{
}
|
T_LEFT_PAR expr T_RIGHT_PAR
{
}
|
functioncall
{
}
;

functioncall:
T_ID T_LEFT_PAR arglist T_RIGHT_PAR
{
}
|
T_ID T_LEFT_PAR T_RIGHT_PAR
{
}
;

arglist:
arglist T_COMMA expr
{
}
|
expr
{
}
;

varassign:
varlist T_ASSIGN assignlist
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::AssignVariable($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
;

varlist:
varlist T_COMMA T_ID
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ParseVarNames($1, std::string($3));
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_ID
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ParseVarNames(nullptr, std::string($1));
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
varlist T_COMMA T_ID T_LEFT_BRACKET expr T_RIGHT_BRACKET
{
    if($1 == nullptr || $3 == nullptr || $5 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ParseVarNames($1, std::string($3), $5);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_ID T_LEFT_BRACKET expr T_RIGHT_BRACKET
{
    if($3 == nullptr || $1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ParseVarNames(nullptr, std::string($1), $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
;

assignlist:
assignlist T_COMMA expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ParseAssignExpressions($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ParseAssignExpressions(nullptr, $1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}   
;

%%


