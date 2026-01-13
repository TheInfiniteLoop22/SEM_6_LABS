// Question:
// 1. To count the number of lines and characters in a file

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char ch;
    int characters = 0;
    int lines = 0;

    //This is to handle imjproper input format
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    //Opening File 1
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    while ((ch = getc(file)) != EOF) {
        characters++;
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);

    printf("Lines: %d\n", lines);
    printf("Characters: %d\n", characters);

    return 0;
}

// Output
/*
Lines: 8
Characters: 168
*/
