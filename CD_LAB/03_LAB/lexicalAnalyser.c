#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define BUFFER_SIZE 4096
#define MAX_LEXEME 100

struct token{
    char lexeme[MAX_LEXEME];
    char type[20];
    int row;
    int col;
};

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

int isSpecialSymbol(char c){
    return (c=='('||c==')'||c=='{'||c=='}'|| c=='['||c==']'||c==';'||c==',');
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

    if(c=='\0'){
        strcpy(tk.type,"EOF");
        return tk;
    }

    if(c=='#'){
        skipPreprocessor();
        goto start;
    }

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

    if(c=='"'){
        while(peekChar()!='"' && peekChar()!='\0')advanceChar();
        advanceChar();

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';
        strcpy(tk.type,"STRING_LITERAL");
        return tk;
    }

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

    if(c=='=' && peekChar()=='='){
        advanceChar();
        strcpy(tk.lexeme,"==");
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    if(c=='!' && peekChar()=='='){
        advanceChar();
        strcpy(tk.lexeme,"!=");
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    if(c=='<' && peekChar()=='='){
        advanceChar();
        strcpy(tk.lexeme,"<=");
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    if(c=='>' && peekChar()=='='){
        advanceChar();
        strcpy(tk.lexeme,">=");
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    if((c=='&'&&peekChar()=='&')||(c=='|'&&peekChar()=='|')){
        advanceChar();
        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';
        strcpy(tk.type,"LOGICAL_OP");
        return tk;
    }

    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"ARITH_OP");
        return tk;
    }

    if(c=='<'||c=='>'){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"REL_OP");
        return tk;
    }

    if(c=='!'){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"LOGICAL_OP");
        return tk;
    }

    if(c=='='){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"ASSIGN_OP");
        return tk;
    }

    if(isSpecialSymbol(c)){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"SYMBOL");
        return tk;
    }

    tk.lexeme[0]=c; tk.lexeme[1]='\0';
    strcpy(tk.type,"UNKNOWN");
    return tk;
}

int main(){
    FILE *fp=fopen("sample.c","r");
    if(!fp){
        printf("File cannot be opened\n");
        return 0;
    }

    struct token tk;
    printf("\n----- TOKENS-----\n");

    while(1){
        tk=getNextToken(fp);
        if(strcmp(tk.type,"EOF")==0) break;

        printf("<%s, %s, Row: %d, Col: %d>\n",
               tk.lexeme,tk.type,tk.row,tk.col);
    }

    fclose(fp);
    return 0;
}


