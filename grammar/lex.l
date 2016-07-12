%{
    #include <stdio.h>
    #include <stdarg.h>
    #include <string>
    #include <map>
    #include <iostream>
    #include <vector>
    #include "Semantic/VarAssign.h"
    #include "Semantic/Statement.h"
    #include "Semantic/Expression.h"
    #include "Exceptions/CedompException.h"
    #include "AST/AST.h"
    #define YY_DECL int yylex()
    #include "parser.tab.h"
    extern int yylineno;
    void yyerror(const char* s, ...);
    bool processString(std::string** str);
%}

%option noyywrap nodefault yylineno

%%

[ \t]   ;

\n     {
    return T_NL;
}

\#[^\n]*\n    ;

"def" {
    return T_DEF;
}

"else" {
    return T_ELSE;
}

"end" {
    return T_END;
}

"return" {
    return T_RETURN;
}

"while" {
    return T_FOR;
}

"if" {
    return T_IF;
}

"map" {
    std::map<std::string, void*>* dict = new std::map<std::string, void*>();
    yylval.maptype = dict;
    return T_MAP;
}

"list" {
    std::vector<void*>* list = new std::vector<void*>;
    yylval.listtype = list;
    return T_LIST;
}

"true" {
    return T_TRUE;
}

"false" {
    return T_FALSE;
}

"and" {
    return T_AND;
}

"xor" {
    return T_XOR;
}

"or" {
    return T_OR;
}

"mod" {
    return T_MOD;
}

"not" {
    return T_NOT;
}

(\'(\\.|[^'])*\')|(\"(\\.|[^"])*\") {
    std::string toProcess(strdup(yytext));
    std::string* result = new std::string();
    for(int i = 1; i < toProcess.size() - 1; ++i)
    {
        *(result) += toProcess[i];
    }
    processString(&result);
    yylval.strtype = result;
    return T_STRING;
}

([a-z]|[A-Z])([a-z]|[A-Z]|[0-9]|\_)* {
    yylval.id = strdup(yytext);
    return T_ID;
}

[0-9]* {
    long* result = new long;
    *(result) = atoi(yytext);
    yylval.inttype = result;
    return T_INT;
}

[0-9]+\.[0-9]+ {
    double* result = new double;
    *(result) = atof(yytext);
    yylval.floattype = result;
    return T_FLOAT;
}

";"  {
    return T_SEMICOLON;
}

","  {
    return T_COMMA;
}

"(" {
    return T_LEFT_PAR;
}

")" {
    return T_RIGHT_PAR;
}

"[" {
    return T_LEFT_BRACKET;
}

"]" {
    return T_RIGHT_BRACKET;
}

"==" {
    return T_EQUALS;
}

"!=" {
    return T_DIFFERENT;
}

">=" {
    return T_GREATER_EQUAL;
}

"<=" {
    return T_LESS_EQUAL;
}

"=" {
    return T_ASSIGN;
}

">" {
    return T_GREATER;
}

"<" {
    return T_LESS;
}

\+ {
    return T_PLUS;
}

\* {
    return T_STAR;
}

\/ {
    return T_SLASH;
}

\- {
    return T_MINUS;
}

":" {
    return T_COLON;
}

. {
    yyerror("unknown token", *yytext);
}

%%

void yyerror(const char* s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "[Line %d] Error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

bool processString(std::string** src)
{
    char curr, lookahead;
    std::string* str = *src;
    std::string* out = new std::string();
    for(int i = 0; i < str->size(); ++i)
    {
        curr = (*str)[i];
        if(curr == '\\')
        {
            ++i;
            if(i == str->size())
            {
                return false;
            }
            else 
            {
                lookahead = (*str)[i];
                switch(lookahead)
                {
                    case 'n':
                    {
                        (*out) += '\n';
                        break;                        
                    }
                    case 'b':
                    {
                        (*out) += '\b';
                        break;
                    }
                    case 'f':
                    {
                        (*out) += '\f';
                        break;
                    }
                    case 'r':
                    {
                        (*out) += '\r';
                        break;
                    }
                    case 't':
                    {
                        (*out) += '\t';
                        break;
                    }
                    case 'v':
                    {
                        (*out) += '\v';
                        break;
                    }
                    case 'a':
                    {
                        (*out) += '\a';
                        break;
                    }
                    default:
                    {
                        (*out) += lookahead;
                        break;
                    }
                }
            }
        }
        else if(curr == '\n' || curr == '\t')
        {
            continue;
        }
        else
        {
            (*out) += curr;
        }
    }
    delete str;
    *src = out;
    return true;    
}


