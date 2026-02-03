#include <stdio.h>

int main() {
    int x;
    WRITE("Enter number: ");
    READ("%d",&x);
    WRITE("Value = %d", x);
}
