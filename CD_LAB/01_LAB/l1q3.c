#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *file1, *file2, *result;
    char line1[256], line2[256];

    if (argc != 4) {
        printf("Usage: %s <filename1> <filename2> <filename3> \n", argv[0]);
        return 1;
    }
    
    file1 = fopen(argv[1], "r");
    if (file1 == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    file2 = fopen(argv[2], "r");
    if (file2 == NULL) {
        printf("Error: Could not open file %s\n", argv[2]);
        fclose(file1);
        return 1;
    }

    result = fopen(argv[3], "w");
    if (result == NULL) {
        printf("Error: Could not open file %s\n", argv[3]);
        fclose(file1);
        fclose(file2);
        return 1;
    }

    while (1) {
        // take one line from file1 nd put it in result
        if (fgets(line1, sizeof(line1), file1) != NULL) {
            fputs(line1, result);
        }
        // take one line from file2 nd put it in result
        if (fgets(line2, sizeof(line2), file2) != NULL) {
            fputs(line2, result);
        }

        if (feof(file1) && feof(file2)) {
            break;
        }
    }

    fclose(file1);
    fclose(file2);
    fclose(result);

    printf("Files merged alternately\n");

    return 0;
}

