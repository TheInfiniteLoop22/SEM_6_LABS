#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

FILE *fp;
struct token tkn;

/* ---------- ERROR ---------- */
void error(char *expected){
    printf("ERROR at row %d col %d: expected %s but found %s\n",
           tkn.row, tkn.col, expected, tkn.lexeme);
    exit(1);
}

/* ---------- SINGLE MATCH ---------- */
void match(char *lex){
    if(strcmp(tkn.lexeme, lex) == 0)
        tkn = getNextToken(fp);
    else
        error(lex);
}

/* ---------- FUNCTION DECLARATIONS ---------- */
void program();
void declarations();
void data_type();
void identifier_list();
void identifier_list_prime();
void statement_list();
void statement();
void assign_stat();
void decision_stat();
void dprime();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

/* ---------- PROGRAM ---------- */
/* Program → main ( ) { Declarations StatementList } */
void program(){
    match("main");
    match("(");
    match(")");
    match("{");

    declarations();
    statement_list();

    match("}");
}

/* ---------- DECLARATIONS ---------- */
/* Declarations → DataType IdentifierList ; Declarations | ε */
void declarations(){
    if(strcmp(tkn.lexeme,"int")==0 || strcmp(tkn.lexeme,"char")==0){
        data_type();
        identifier_list();
        match(";");
        declarations();
    }
}

/* ---------- DATA TYPE ---------- */
/* DataType → int | char */
void data_type(){
    if(strcmp(tkn.lexeme,"int")==0)
        match("int");
    else if(strcmp(tkn.lexeme,"char")==0)
        match("char");
    else
        error("int or char");
}

/* ---------- IDENTIFIER LIST ---------- */
/* IdentifierList → id [num] IdentifierList' */
void identifier_list(){

    if(strcmp(tkn.type,"ID")==0)
        tkn = getNextToken(fp);
    else
        error("ID");

    if(strcmp(tkn.lexeme,"[")==0){
        match("[");
        if(strcmp(tkn.type,"NUM")==0)
            tkn = getNextToken(fp);
        else
            error("NUM");
        match("]");
    }

    identifier_list_prime();
}

/* IdentifierList' → , IdentifierList | ε */
void identifier_list_prime(){
    if(strcmp(tkn.lexeme,",")==0){
        match(",");
        identifier_list();
    }
}

/* ---------- STATEMENTS ---------- */
/* StatementList → Statement StatementList | ε */
void statement_list(){
    if(strcmp(tkn.lexeme,"if")==0 || strcmp(tkn.type,"ID")==0){
        statement();
        statement_list();
    }
}

/* Statement → AssignStat ; | DecisionStat */
void statement(){
    if(strcmp(tkn.lexeme,"if")==0)
        decision_stat();
    else if(strcmp(tkn.type,"ID")==0)
        assign_stat();
    else
        error("if or ID");
}

/* ---------- ASSIGNMENT ---------- */
/* AssignStat → id = Expn ; */
void assign_stat(){

    if(strcmp(tkn.type,"ID")==0)
        tkn = getNextToken(fp);
    else
        error("ID");

    match("=");
    expn();
    match(";");
}

/* ---------- IF-ELSE ---------- */
/* DecisionStat → if ( Expn ) { StatementList } Dprime */
void decision_stat(){
    match("if");
    match("(");
    expn();
    match(")");
    match("{");
    statement_list();
    match("}");
    dprime();
}

/* Dprime → else { StatementList } | ε */
void dprime(){
    if(strcmp(tkn.lexeme,"else")==0){
        match("else");
        match("{");
        statement_list();
        match("}");
    }
}

/* ---------- EXPRESSIONS ---------- */
/* Expn → SimpleExpn Eprime */
void expn(){
    simple_expn();
    eprime();
}

/* Eprime → Relop SimpleExpn | ε */
void eprime(){
    if(strcmp(tkn.type,"REL_OP")==0){
        relop();
        simple_expn();
    }
}

/* SimpleExpn → Term Seprime */
void simple_expn(){
    term();
    seprime();
}

/* Seprime → Addop Term Seprime | ε */
void seprime(){
    if(strcmp(tkn.lexeme,"+")==0 || strcmp(tkn.lexeme,"-")==0){
        addop();
        term();
        seprime();
    }
}

/* Term → Factor Tprime */
void term(){
    factor();
    tprime();
}

/* Tprime → Mulop Factor Tprime | ε */
void tprime(){
    if(strcmp(tkn.lexeme,"*")==0 || strcmp(tkn.lexeme,"/")==0 || strcmp(tkn.lexeme,"%")==0){
        mulop();
        factor();
        tprime();
    }
}

/* Factor → id | num */
void factor(){
    if(strcmp(tkn.type,"ID")==0)
        tkn = getNextToken(fp);
    else if(strcmp(tkn.type,"NUM")==0)
        tkn = getNextToken(fp);
    else
        error("ID or NUM");
}

/* ---------- OPERATORS ---------- */
/* Relop → == | != | <= | >= | < | > */
void relop(){
    if(strcmp(tkn.type,"REL_OP")==0)
        tkn = getNextToken(fp);
    else
        error("Relational Operator");
}

/* Addop → + | - */
void addop(){
    if(strcmp(tkn.lexeme,"+")==0 || strcmp(tkn.lexeme,"-")==0)
        tkn = getNextToken(fp);
    else
        error("+ or -");
}

/* Mulop → * | / | % */
void mulop(){
    if(strcmp(tkn.lexeme,"*")==0 || strcmp(tkn.lexeme,"/")==0 || strcmp(tkn.lexeme,"%")==0)
        tkn = getNextToken(fp);
    else
        error("* or / or %");
}

/* ---------- MAIN ---------- */
int main(){
    fp = fopen("input.c","r");
    if(!fp){
        printf("File not found\n");
        return 0;
    }

    tkn = getNextToken(fp);

    program();

    if(strcmp(tkn.type,"EOF")==0)
        printf("SUCCESS\n");
    else
        printf("ERROR: Extra tokens\n");

    fclose(fp);
    return 0;
}