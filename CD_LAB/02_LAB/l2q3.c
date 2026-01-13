/*
Question 3: That takes C program as input, recognizes all the keywords and prints them in upper case.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", 
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

#define KEYWORD_COUNT 32

int isKeyword(char *word)
{
    for (int i = 0; i < KEYWORD_COUNT; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void toUpperCase(char *word)
{
    for (int i = 0; word[i]; i++)
        word[i] = toupper(word[i]);
}

int main(int argc, char *argv[])
{
    FILE *inputFile, *outputFile;
    char ch, word[100];
    int index = 0;

    if (argc != 3)
    {
        printf("Usage: %s <input.c> <output.c>\n", argv[0]);
        return 1;
    }

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(inputFile)) != EOF)
    {
        if (isalnum(ch) || ch == '_')
        {
            word[index++] = ch;
        }
        else
        {
            if (index > 0)
            {
                word[index] = '\0';

                if (isKeyword(word))
                { toUpperCase(word); }

                fputs(word, outputFile);
                index = 0;
            }

            fputc(ch, outputFile);
        }
    }
	
    // This is to deal with the condition of the last word in the file being a keyword.
    if (index > 0)
    {
        word[index] = '\0';
        if (isKeyword(word))
        {
            toUpperCase(word);
        }
        fputs(word, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Keywords converted to uppercase successfully.\n");
    return 0;
}

