#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define BUFFER_SIZE 4096
#define MAX_LEXEME 100

/* ================= TOKEN STRUCT ================= */
struct token{
    char lexeme[MAX_LEXEME];
    char type[20];
    int row;
    int col;
};

/* ================= GLOBALS ================= */
static char buffer[BUFFER_SIZE];
static int bufSize=0;
static int LB=0,FP=0;
static int row=1,col=1;
static int initialized=0;


/* ================= KEYWORDS (Perl) ================= */
const char *keywords[]={
    "scalar","foreach"
};

int keywordCount = sizeof(keywords)/sizeof(keywords[0]);


/* ================= BUFFER LOAD ================= */
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


/* ================= HELPERS ================= */
int isKeyword(char *str){
    for(int i=0;i<keywordCount;i++)
        if(strcmp(str,keywords[i])==0) return 1;
    return 0;
}

void skipWhiteSpace(){
    while(peekChar()==' '||peekChar()=='\t'||peekChar()=='\n')
        advanceChar();
}

/* Perl comment (# or #!) */
void skipComment(){
    while(peekChar()!='\n' && peekChar()!='\0')
        advanceChar();
}


/* ================= LEXER ================= */
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

    /* EOF */
    if(c=='\0'){
        strcpy(tk.type,"EOF");
        return tk;
    }

    /* comments or shebang */
    if(c=='#'){
        skipComment();
        goto start;
    }

    /* @_ special token */
    if(c=='@' && peekChar()=='_'){
        advanceChar();
        strcpy(tk.lexeme,"@_");
        strcpy(tk.type,"SPECIAL");
        return tk;
    }

    /* $variable (single token) */
    if(c=='$'){
        while(isalnum(peekChar())||peekChar()=='_')
            advanceChar();

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';

        strcpy(tk.type,"ID");
        return tk;
    }

    /* identifiers / keywords */
    if(isalpha(c)){
        while(isalnum(peekChar())||peekChar()=='_')
            advanceChar();

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';

        if(isKeyword(tk.lexeme))
            strcpy(tk.type,"KEYWORD");
        else
            strcpy(tk.type,"ID");

        return tk;
    }

    /* numbers */
    if(isdigit(c)){
        while(isdigit(peekChar()))
            advanceChar();

        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';

        strcpy(tk.type,"NUM");
        return tk;
    }

    /* += compound operator */
    if(c=='+' && peekChar()=='='){
        advanceChar();
        strcpy(tk.lexeme,"+=");
        strcpy(tk.type,"ASSIGN_OP");
        return tk;
    }

    /* single arithmetic */
    if(c=='+'||c=='-'||c=='*'||c=='/'){
        tk.lexeme[0]=c;
        tk.lexeme[1]='\0';
        strcpy(tk.type,"ARITH_OP");
        return tk;
    }

    /* symbols */
    if(c=='('||c==')'||c=='{'||c=='}'||c==';'){
        tk.lexeme[0]=c;
        tk.lexeme[1]='\0';
        strcpy(tk.type,"SYMBOL");
        return tk;
    }

    /* default */
    tk.lexeme[0]=c;
    tk.lexeme[1]='\0';
    strcpy(tk.type,"UNKNOWN");
    return tk;
}


/* ================= DRIVER ================= */
int main(){

    FILE *fp=fopen("sample.pl","r");
    if(!fp){
        printf("Cannot open file\n");
        return 0;
    }

    struct token tk;

    printf("\n--- TOKENS ---\n");

    while(1){
        tk=getNextToken(fp);

        if(strcmp(tk.type,"EOF")==0)
            break;

        printf("<%s , %s , Row:%d , Col:%d>\n",
               tk.lexeme,tk.type,tk.row,tk.col);
    }

    fclose(fp);
}

/*
--- TOKENS ---
<$n , ID , Row:4 , Col:1>
<= , UNKNOWN , Row:4 , Col:4>
<scalar , KEYWORD , Row:4 , Col:6>
<( , SYMBOL , Row:4 , Col:12>
<@_ , SPECIAL , Row:4 , Col:13>
<) , SYMBOL , Row:4 , Col:15>
<; , SYMBOL , Row:4 , Col:16>
<$sum , ID , Row:5 , Col:1>
<= , UNKNOWN , Row:5 , Col:6>
<0 , NUM , Row:5 , Col:8>
<; , SYMBOL , Row:5 , Col:9>
<foreach , KEYWORD , Row:7 , Col:1>
<$item , ID , Row:7 , Col:9>
<( , SYMBOL , Row:7 , Col:14>
<@_ , SPECIAL , Row:7 , Col:15>
<) , SYMBOL , Row:7 , Col:17>
<{ , SYMBOL , Row:7 , Col:19>
<$sum , ID , Row:8 , Col:5>
<+= , ASSIGN_OP , Row:8 , Col:10>
<$item , ID , Row:8 , Col:13>
<; , SYMBOL , Row:8 , Col:18>
<} , SYMBOL , Row:9 , Col:1>
<$average , ID , Row:11 , Col:1>
<= , UNKNOWN , Row:11 , Col:10>
<$sum , ID , Row:11 , Col:12>
<+ , ARITH_OP , Row:11 , Col:17>
<$n , ID , Row:11 , Col:19>
<; , SYMBOL , Row:11 , Col:21>
*/