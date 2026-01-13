/*
Ouestion 1: That takes a file as input and replaces blank spaces and tabs by single space and writes the output to a file.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *inputFile, *outputFile;
    int ch;
    int prevSpace = 0;

    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    outputFile = fopen(argv[2], "w");
    if (outputFile == NULL)
    {
        printf("Error: Could not open output file.\n");
        fclose(inputFile);
        return 1;
    }

    while ((ch = fgetc(inputFile)) != EOF)
    {
        if (ch == ' ' || ch == '\t')
        {
            if (!prevSpace)
            {
                fputc(' ', outputFile);
                prevSpace = 1;
            }
        }
        else
        {
            fputc(ch, outputFile);
            prevSpace = 0;
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File processed successfully.\n");
    return 0;
}

