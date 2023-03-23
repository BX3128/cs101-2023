#include <stdio.h>
void replace_all(char* str, char oldChar, char newChar) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
        i++;
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
