/*
Question 2: To discard preprocessor directives from the given input ‘C’ file.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *inputFile, *outputFile;
    char line[1000];

    if (argc != 3)
    {
        printf("Usage: %s <input_file.c> <output_file.c>\n", argv[0]);
        return 1;
    }

    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    outputFile = fopen(argv[2], "w");
    if (outputFile == NULL)
    {
        printf("Error: Cannot open output file.\n");
        fclose(inputFile);
        return 1;
    }

    while (fgets(line, sizeof(line), inputFile))
    {
        if (line[0] != '#')
        {
            fputs(line, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Output File Ready! \n");
    return 0;
}

