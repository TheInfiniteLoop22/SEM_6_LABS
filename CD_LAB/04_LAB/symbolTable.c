/*
Question
Using getNextToken( ) implemented in Lab No 3, design a Lexical Analyser to implement the local symbol table looks like:
Lexeme name      |     type    | size    |   returnType
FuncName               func      0           int/void/char
identifierName         int       4           -  

search() and insert() to prevent repeated entries.
hashing shld be implemented.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.h"

#define TABLE_SIZE 101
#define MAX 100

struct symbol{
    char name[MAX];
    char type[20];
    int size;
    char returnType[20];
    struct symbol *next;
};

struct symbol *symTable[TABLE_SIZE]={NULL};

int hash(char *str){
    int h=0;
    while(*str)
        h=(h*31+*str++)%TABLE_SIZE;
    return h;
}

struct symbol* search(char *name){
    int index=hash(name);
    struct symbol *t=symTable[index];
    while(t){
        if(strcmp(t->name,name)==0) return t;
        t=t->next;
    }
    return NULL;
}

void insertSymbol(char *name,char *type,int size,char *ret){
    if(search(name)) return;

    int index=hash(name);
    struct symbol *n=malloc(sizeof(struct symbol));

    strcpy(n->name,name);
    strcpy(n->type,type);
    n->size=size;
    strcpy(n->returnType,ret);

    n->next=symTable[index];
    symTable[index]=n;
}

int getSize(char *d){
    if(strcmp(d,"int")==0) return 4;
    if(strcmp(d,"float")==0) return 4;
    if(strcmp(d,"double")==0) return 8;
    if(strcmp(d,"char")==0) return 1;
    return 0;
}

void printSymbolTable(){
    printf("\nLexeme          Type       Size     ReturnType\n");
    printf("---------------------------------------------\n");

    for(int i=0;i<TABLE_SIZE;i++){
        struct symbol *t=symTable[i];
        while(t){
            printf("%-15s %-10s %-8d %-10s\n",
                   t->name,t->type,t->size,t->returnType);
            t=t->next;
        }
    }
}

int main(){
    FILE *fp=fopen("sample.c","r");
    if(!fp) return 0;

    struct token tk,nextTk;

    char currentType[20]="";
    int currentSize=0;

    while(1){
        tk=getNextToken(fp);
        if(strcmp(tk.type,"EOF")==0) break;

        if(strcmp(tk.type,"KEYWORD")==0){
            strcpy(currentType,tk.lexeme);
            currentSize=getSize(tk.lexeme);
        }
        else if(strcmp(tk.type,"ID")==0){
            nextTk=getNextToken(fp);

            if(strcmp(nextTk.type,"SYMBOL")==0 && strcmp(nextTk.lexeme,"(")==0)
                insertSymbol(tk.lexeme,"func",0,currentType);
            else
                insertSymbol(tk.lexeme,currentType,currentSize,"-");
        }
    }

    fclose(fp);
    printSymbolTable();
    return 0;
}

