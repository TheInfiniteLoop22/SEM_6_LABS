//2. To reverse the file contents and store in another file. Also display the size of file using file handling function.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source, *target;
    long size;
    char ch;

    if (argc != 3) {
        printf("Usage: %s <filename1> <filename2> \n", argv[0]);
        return 1;
    }

    source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    
    target = fopen(argv[2], "w");
    if (target == NULL) {
        printf("Error: Could not open file %s\n", argv[2]);
        fclose(source);
        return 1;
    }

    fseek(source, 0, SEEK_END);
    size = ftell(source);

    printf("Size of file: %ld bytes\n", size);

    for (long i = size - 1; i >= 0; i--) {
        fseek(source, i, SEEK_SET);
        ch = getc(source);
        putc(ch, target);
    }

    fclose(source);
    fclose(target);

    printf("File contents reversed successfully.\n");

    return 0;
}

//Ouput:
/*
Size of file: 45 bytes
File contents reversed successfully.
*/

