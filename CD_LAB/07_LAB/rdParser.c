#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

struct token tkn;
FILE *fp;

/* Function declarations */
void Program();
void Declarations();
void Data_type();
void Identifier_list();
void Identifier_list_prime();
void Identifier_list_double_prime();
void Statement_list();
void Statement();
void Assign_stat();
void Expn();
void Eprime();
void Simple_exp();
void Seprime();
void Term();
void Tprime();
void Factor();
void Decision_stat();
void Dprime();

void error(char *msg){
    printf("Syntax error at row %d col %d: expected %s but found %s\n",
           tkn.row,tkn.col,msg,tkn.lexeme);
    exit(1);
}

void matchLexeme(char *lex){
    if(strcmp(tkn.lexeme,lex)==0)
        tkn=getNextToken(fp);
    else
        error(lex);
}

void matchType(char *type){
    if(strcmp(tkn.type,type)==0)
        tkn=getNextToken(fp);
    else
        error(type);
}

/* Program → main ( ) { Declarations Statement_list } */
void Program(){
    matchLexeme("main");
    matchLexeme("(");
    matchLexeme(")");
    matchLexeme("{");

    Declarations();
    Statement_list();

    matchLexeme("}");
    printf("Parsing Successful\n");
}

/* Declarations → Data_type Identifier_list ; Declarations | ε */
void Declarations(){
    if(strcmp(tkn.lexeme,"int")==0 ||
       strcmp(tkn.lexeme,"char")==0){
        Data_type();
        Identifier_list();
        matchLexeme(";");
        Declarations();
    }
}

/* Data_type → int | char */
void Data_type(){
    if(strcmp(tkn.lexeme,"int")==0 ||
       strcmp(tkn.lexeme,"char")==0)
        tkn=getNextToken(fp);
    else
        error("int or char");
}

/* Identifier_list → id Identifier_list' */
void Identifier_list(){
    matchType("ID");
    Identifier_list_prime();
}

/* Identifier_list' */
void Identifier_list_prime(){
    if(strcmp(tkn.lexeme,"[")==0){
        matchLexeme("[");
        matchType("NUM");
        matchLexeme("]");
        Identifier_list_double_prime();
    }
    else if(strcmp(tkn.lexeme,",")==0){
        matchLexeme(",");
        Identifier_list();
    }
}

/* Identifier_list'' */
void Identifier_list_double_prime(){
    if(strcmp(tkn.lexeme,",")==0){
        matchLexeme(",");
        Identifier_list();
    }
}

/* Statement_list → Statement Statement_list | ε */
void Statement_list(){
    if(strcmp(tkn.type,"ID")==0 ||
       strcmp(tkn.lexeme,"if")==0){
        Statement();
        Statement_list();
    }
}

/* Statement → Assign_stat | Decision_stat */
void Statement(){
    if(strcmp(tkn.type,"ID")==0)
        Assign_stat();
    else if(strcmp(tkn.lexeme,"if")==0)
        Decision_stat();
    else
        error("Statement");
}

/* Assign_stat → id = Expn ; */
void Assign_stat(){
    matchType("ID");
    matchLexeme("=");
    Expn();
    matchLexeme(";");
}

/* Expn → Simple_exp Eprime */
void Expn(){
    Simple_exp();
    Eprime();
}

/* Eprime → Relop Simple_exp | ε */
void Eprime(){
    if(strcmp(tkn.lexeme,"==")==0 ||
       strcmp(tkn.lexeme,"!=")==0 ||
       strcmp(tkn.lexeme,"<")==0 ||
       strcmp(tkn.lexeme,">")==0 ||
       strcmp(tkn.lexeme,"<=")==0 ||
       strcmp(tkn.lexeme,">=")==0){
        tkn=getNextToken(fp);
        Simple_exp();
    }
}

/* Simple_exp → Term Seprime */
void Simple_exp(){
    Term();
    Seprime();
}

/* Seprime → Addop Term Seprime | ε */
void Seprime(){
    if(strcmp(tkn.lexeme,"+")==0 ||
       strcmp(tkn.lexeme,"-")==0){
        tkn=getNextToken(fp);
        Term();
        Seprime();
    }
}

/* Term → Factor Tprime */
void Term(){
    Factor();
    Tprime();
}

/* Tprime → Mulop Factor Tprime | ε */
void Tprime(){
    if(strcmp(tkn.lexeme,"*")==0 ||
       strcmp(tkn.lexeme,"/")==0 ||
       strcmp(tkn.lexeme,"%")==0){
        tkn=getNextToken(fp);
        Factor();
        Tprime();
    }
}

/* Factor → id | number */
void Factor(){
    if(strcmp(tkn.type,"ID")==0)
        matchType("ID");
    else if(strcmp(tkn.type,"NUM")==0)
        matchType("NUM");
    else
        error("ID or NUM");
}

/* Decision_stat → if ( Expn ) { Statement_list } Dprime */
void Decision_stat(){
    matchLexeme("if");
    matchLexeme("(");
    Expn();
    matchLexeme(")");
    matchLexeme("{");
    Statement_list();
    matchLexeme("}");
    Dprime();
}

/* Dprime → else { Statement_list } | ε */
void Dprime(){
    if(strcmp(tkn.lexeme,"else")==0){
        matchLexeme("else");
        matchLexeme("{");
        Statement_list();
        matchLexeme("}");
    }
}

int main(){
    fp=fopen("source.c","r");
    if(!fp){
        printf("File error\n");
        return 1;
    }

    tkn=getNextToken(fp);
    Program();

    fclose(fp);
    return 0;
}