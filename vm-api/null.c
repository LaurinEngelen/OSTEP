#include <stdio.h>

int main() {
    int *ptr = NULL;  // Ein Zeiger auf einen int, der auf NULL gesetzt wird.
    printf("%d\n", *ptr);  // Versuch, den Null-Zeiger zu dereferenzieren.
    return 0;
}
