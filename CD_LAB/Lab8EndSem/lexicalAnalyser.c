#include "la.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 

#define BUFFER_SIZE 4096
#define MAX_LEXEME 100

static char buffer[BUFFER_SIZE];
static int bufSize=0;
static int LB=0,FP=0;
static int row=1,col=1;
static int initialized=0;

const char *keywords[]={
 "int","float","double","char","void","long","short","signed","unsigned",
 "if","else","while","for","do","switch","case","default",
 "break","continue","return","goto",
 "auto","register","static","extern","const","volatile",
 "struct","union","enum","typedef","sizeof",
 "printf","scanf","malloc","free","strlen","strcpy","strcmp","exit",
 "main"
};

int keywordCount = sizeof(keywords)/sizeof(keywords[0]);

void loadBuffer(FILE *fp){
    bufSize=fread(buffer,1,BUFFER_SIZE-1,fp);
    buffer[bufSize]='\0';
}

char advanceChar(){
    char c=buffer[FP++];
    if(c=='\n'){ row++; col=1; }
    else col++;
    return c;
}

char peekChar(){ return buffer[FP]; }

int isKeyword(char *str){
    for(int i=0;i<keywordCount;i++)
        if(strcmp(str,keywords[i])==0) return 1;
    return 0;
}

void skipWhiteSpace(){
    while(peekChar()==' '||peekChar()=='\t'||peekChar()=='\n') advanceChar();
}

void skipSingleLineComment(){
    while(advanceChar()!='\n');
}

void skipMultiLineComment(){
    char c;
    while(FP<bufSize){
        c=advanceChar();
        if(c=='*' && peekChar()=='/'){
            advanceChar();
            break;
        }
    }
}

void skipPreprocessor(){
    while(advanceChar()!='\n');
}

struct token getNextToken(FILE *fp){
    struct token tk;
    if(!initialized){
        loadBuffer(fp);
        initialized=1;
    }

start:
    skipWhiteSpace();

    tk.row=row;
    tk.col=col;

    LB=FP; 
    
    char c=advanceChar();

    /* Check for end of file (EOF) */
    if(c=='\0'){
        strcpy(tk.type,"EOF");
        return tk;
    }

    /* Handle preprocessor directives */
    if(c=='#'){
        skipPreprocessor();
        goto start;
    }

    /* Handle comments */
    if(c=='/'){
        if(peekChar()=='/'){
            advanceChar();
            skipSingleLineComment();
            goto start;
        }
        if(peekChar()=='*'){
            advanceChar();
            skipMultiLineComment();
            goto start;
        }
    }

    /* character literal */
    if(c=='\''){
        while(peekChar()!='\'' && peekChar()!='\0'){
            advanceChar();
        }
        advanceChar();  // closing quote

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';

        strcpy(tk.type,"CHAR_LITERAL");
        return tk;
    }

    /* Handle string literals */
    if(c=='"'){
        while(peekChar()!='"' && peekChar()!='\0')advanceChar();
        advanceChar();

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';
        strcpy(tk.type,"STRING_LITERAL");
        return tk;
    }

    /* Handle identifiers and keywords */
    if(isalpha(c)||c=='_'){
        while(isalnum(peekChar())||peekChar()=='_')
            advanceChar();

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';

        if(isKeyword(tk.lexeme)) strcpy(tk.type,"KEYWORD");
        else strcpy(tk.type,"ID");
        return tk;
    }

    /* Handle numeric literals */
    if(isdigit(c)){
        while(isdigit(peekChar())) advanceChar();
        if(peekChar()=='.'){
            advanceChar();
            while(isdigit(peekChar())) advanceChar();
        }

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';
        strcpy(tk.type,"NUM");
        return tk;
    }

    /* -------- OPERATORS -------- */

    /* ---- 2-CHAR OPERATORS ---- */

    /* Relational: == != <= >= */
    if((c=='='||c=='!'||c=='<'||c=='>') && peekChar()=='='){
        char first = c;
        advanceChar();
        tk.lexeme[0]=first;
        tk.lexeme[1]='=';
        tk.lexeme[2]='\0';
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    /* Logical: && || */
    if((c=='&' && peekChar()=='&') || (c=='|' && peekChar()=='|')){
        char first = c;
        advanceChar();
        tk.lexeme[0]=first;
        tk.lexeme[1]=first;
        tk.lexeme[2]='\0';
        strcpy(tk.type,"LOGICAL_OP");
        return tk;
    }

    /* Arithmetic: ++ -- */
    if((c=='+' && peekChar()=='+') || (c=='-' && peekChar()=='-')){
        char first = c;
        advanceChar();
        tk.lexeme[0]=first;
        tk.lexeme[1]=first;
        tk.lexeme[2]='\0';
        strcpy(tk.type,"ARITH_OP");
        return tk;
    }

    /* Assignment: += -= *= /= %= */
    if((c=='+'||c=='-'||c=='*'||c=='/'||c=='%') && peekChar()=='='){
        char first = c;
        advanceChar();
        tk.lexeme[0]=first;
        tk.lexeme[1]='=';
        tk.lexeme[2]='\0';
        strcpy(tk.type,"ASSIGN_OP");
        return tk;
    }


    /* ---- 1-CHAR OPERATORS ---- */

    /* Arithmetic: + - * / % */
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'){
        tk.lexeme[0]=c;
        tk.lexeme[1]='\0';
        strcpy(tk.type,"ARITH_OP");
        return tk;
    }

    /* Relational: < > */
    if(c=='<'||c=='>'){
        tk.lexeme[0]=c;
        tk.lexeme[1]='\0';
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    /* Logical: ! */
    if(c=='!'){
        tk.lexeme[0]=c;
        tk.lexeme[1]='\0';
        strcpy(tk.type,"LOGICAL_OP");
        return tk;
    }

    /* Assignment: = */
    if(c=='='){
        tk.lexeme[0]=c;
        tk.lexeme[1]='\0';
        strcpy(tk.type,"ASSIGN_OP");
        return tk;
    }

    /* Handle special symbols */
    if(c=='('||c==')'||c=='{'||c=='}'|| c=='['||c==']'||c==';'||c==','){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"SYMBOL");
        return tk;
    }

    tk.lexeme[0]=c; tk.lexeme[1]='\0';
    strcpy(tk.type,"UNKNOWN");
    return tk;
}



