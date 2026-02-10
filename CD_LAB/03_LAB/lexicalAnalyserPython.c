#include<stdio.h> // For file handling and I/O operations
#include<stdlib.h> // For dynamic memory allocation and exit function
#include<string.h> // For string manipulation functions like strcmp, strncpy, and strcpy
#include<ctype.h> // For character handling functions like isalpha, isalnum, and isdigit

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

/* Updated keywords for Python */
const char *keywords[]={
 "def","class","if","elif","else","for","while","break","continue",
 "return","import","from","as","pass","True","False","None",
 "and","or","not","in","is","lambda","with","yield","try","except","finally","print"
};


int keywordCount = sizeof(keywords)/sizeof(keywords[0]);

void loadBuffer(FILE *fp){
    bufSize=fread(buffer,1,BUFFER_SIZE-1,fp); // syntax: fread(pointer, size_of_element, number_of_elements, file_pointer)
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
    return (c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'||c==','||c==':'||c=='.');
}

void skipWhiteSpace(){
    while(peekChar()==' '||peekChar()=='\t'||peekChar()=='\n') advanceChar();
}

struct token getNextToken(FILE *fp){
    struct token tk;
    if(!initialized){
        loadBuffer(fp);
        initialized=1;
    }

start:
    skipWhiteSpace(); // Skip any leading whitespace characters

    // Set the row and column information for the token
    tk.row=row;
    tk.col=col;

    LB=FP; // Set the Lexeme Begin (LB) to the current position of the Forward Pointer (FP)
    
    char c=advanceChar();

    /* Check for end of file (EOF) */
    if(c=='\0'){
        strcpy(tk.type,"EOF");
        return tk;
    }

    /* Handle comments */
    if(c=='#'){
        while(peekChar()!='\n' && peekChar()!='\0') advanceChar();
        goto start;
    }

    /* Handle string literals */
    if(c=='"' || c=='\'')
    {
        char quote = c;
        while(peekChar()!=quote && peekChar()!='\0')
            advanceChar();
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

    /* Handle operators */
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

    /* logical operators */
    if((c=='&'&&peekChar()=='&')||(c=='|'&&peekChar()=='|')){
        advanceChar();
        int len=FP-LB;
        strncpy(tk.lexeme,buffer+LB,len);
        tk.lexeme[len]='\0';
        strcpy(tk.type,"LOGICAL_OP");
        return tk;
    }

    /* increment/decrement */
    if((c=='+' && peekChar()=='+') || (c=='-' && peekChar()=='-')){
        advanceChar();
        tk.lexeme[0]=c;
        tk.lexeme[1]=c;
        tk.lexeme[2]='\0';
        strcpy(tk.type,"ARITH_OP");   // or INC_OP if you want
        return tk;
    }

    /* compound assignment */
    if((c=='+'||c=='-'||c=='*'||c=='/'||c=='%') && peekChar()=='='){
        advanceChar();
        tk.lexeme[0]=c;
        tk.lexeme[1]='=';
        tk.lexeme[2]='\0';
        strcpy(tk.type,"ASSIGN_OP");
        return tk;
    }

    /* Handle exponentiation operator (**) */
    if(c=='*' && peekChar()=='*'){
        advanceChar();
        strcpy(tk.lexeme,"**");
        strcpy(tk.type,"ARITH_OP");
        return tk;  
    }

    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'){
        tk.lexeme[0]=c; tk.lexeme[1]='\0';
        strcpy(tk.type,"ARITH_OP");
        return tk;
    }

    /* relational operators */
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

    /* Handle special symbols */
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
    FILE *fp=fopen("sample.py","r");
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


