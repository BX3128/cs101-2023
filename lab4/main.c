#include <stdio.h>
void replace_all(char* str, char oldChar, char newChar) {
    while (*str != '\0') {
        *str == oldChar ? *str = newChar, str++ : str++;
    }
}

int main() {
    char str[100], oldChar = 'a', newChar='A';
    printf("Enter any string: ");
    scanf("%s", str);

    printf("\nString before replacing: \n%s", str);
    replace_all(str, oldChar, newChar);
    printf("\n\nString after replacing %c with %c : \n%s\n", oldChar, newChar, str);

    return 0;
}

// memo
/*

// cost: 9 lines
void replace_all(char* str, char oldChar, char newChar) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
        i++;
    }
}

// cost: 8 lines
void replace_all(char* str, char oldChar, char newChar) {
    while (*str != '\0') {
        if (*str == oldChar) {
            *str = newChar;
        }
        str++;
    }
}

// cost: 6 lines
void replace_all(char* str, char oldChar, char newChar) {
    while (*str != '\0') {
        *str == oldChar ? *str = newChar : 0;
        str++;
    }
}

*/
