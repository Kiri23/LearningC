#include <stdio.h>
#include <string.h> // Include string.h for strcmp function

int main(int argc, char **argv) {

    // this is a string
    char *str = "hehe";

    // create the same string
    // as a character array 
    char otherstr[] = "hehke"; // Initialize otherstr with the same string as str

    if (!strcmp(str, otherstr)) {
        printf("Yay!\n");
    } else {
        printf("Nay!\n");
    }

    return 0;
}