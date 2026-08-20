#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char ciphertext[300];
    int i;

    /* Inverse of
       9 4
       5 7

       is:
       5 12
       15 25
    */

    printf("Enter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("\nDecrypted text: ");

    for (i = 0; ciphertext[i] != '\0'; i += 2)
    {
        if (!isalpha(ciphertext[i]))
        {
            i--;
            continue;
        }

        int c1 = toupper(ciphertext[i]) - 'A';
        int c2 = toupper(ciphertext[i + 1]) - 'A';

        int p1 = (5 * c1 + 12 * c2) % 26;
        int p2 = (15 * c1 + 25 * c2) % 26;

        printf("%c%c", p1 + 'A', p2 + 'A');
    }

    printf("\n");

    return 0;
}