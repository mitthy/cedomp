%{
    #include <string>
    #include <vector>
    #include <map>
    #include <iostream>
    #include "Semantic/VarAssign.h"
    #include "Semantic/Statement.h"
    #include "Semantic/Expression.h"
    #include "AST/AST.h"
    #include "Exceptions/CedompException.h"
    extern int yylex();
    extern int yyparse();
    extern void yyerror(const char* s, ...);
    using std::cout;
    using std::endl;
    Cedomp::AST::AbstractNode* root = nullptr;
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
    Cedomp::AST::BlockNode* typehead;
    Cedomp::AST::BlockNode* typestatements;
    Cedomp::AST::AbstractNode* typestatement;
}

%token T_NL
%token T_SEMICOLON T_COMMA T_LEFT_PAR T_RIGHT_PAR T_LEFT_BRACKET T_RIGHT_BRACKET  T_ASSIGN T_COLON
%token T_MAP T_LIST T_TRUE T_FALSE T_STRING T_ID T_INT T_FLOAT
%token T_DEF T_END T_RETURN T_FOR T_IF T_ELSE
%token T_AND T_XOR T_OR T_MOD T_NOT T_EQUALS T_DIFFERENT T_GREATER_EQUAL T_LESS_EQUAL T_GREATER T_LESS T_PLUS T_STAR T_SLASH T_MINUS

%type<typehead> head
%type<typestatements> statements
%type<typestatement> statement
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
    $$ = $1;
    root = $$;
}
;

statements:
statements statement T_NL
{
    if($1 == nullptr)
    {
        //TODO
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::AddStatement($1, $2);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
statement T_NL
{
    if($1 == nullptr)
    {
        //TODO
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::AddStatement(nullptr, $1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_NL
{
    //Skip
}
|
statements T_NL
{
    //Skip
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
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::AssignVariableStatement($1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
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
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeID($1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_INT
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeInteger($1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_FLOAT
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeFloat($1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_STRING
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeString($1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_MAP T_LEFT_PAR T_RIGHT_PAR
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeMap($1);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_LIST T_LEFT_PAR T_RIGHT_PAR
{
    if($1 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeList($1);
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
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeIndex($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_MOD expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeMod($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_PLUS expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeAddition($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_MINUS expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeSubtraction($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_STAR expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeMultiplication($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_SLASH expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeDivision($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_MINUS expr %prec UNARY_MINUS
{
    if($2 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeUnaryMinus($2);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_GREATER expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeGreaterThan($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_EQUALS expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeEquals($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_GREATER_EQUAL expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeGreaterEquals($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_TRUE
{
    try
    {
        bool* arg = new bool;
        *arg = true;
        $$ = Cedomp::Semantic::ComputeBool(arg);
    }
    catch(Cedomp::Exceptions::CedompException& e)
    {
        $$ = nullptr;
        e.PrintSemanticError();
    }
}
|
T_FALSE
{
    try
    {
        bool* arg = new bool;
        *arg = false;
        $$ = Cedomp::Semantic::ComputeBool(arg);
    }
    catch(Cedomp::Exceptions::CedompException& e)
    {
        $$ = nullptr;
        e.PrintSemanticError();
    }
}
|
expr T_AND expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeAnd($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_XOR expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeXor($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_OR expr 
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeOr($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_NOT expr 
{
    if($2 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeNot($2);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_DIFFERENT expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeDifferent($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_LESS_EQUAL expr 
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeLessEqual($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
expr T_LESS expr
{
    if($1 == nullptr || $3 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeLess($1, $3);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
}
|
T_LEFT_PAR expr T_RIGHT_PAR
{
    if($2 == nullptr)
    {
        $$ = nullptr;
    }
    else
    {
        try
        {
            $$ = Cedomp::Semantic::ComputeEnclosed($2);
        }
        catch(Cedomp::Exceptions::CedompException& e)
        {
            $$ = nullptr;
            e.PrintSemanticError();
        }
    }
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


