#include <stdio.h>

int main()
{
    char ciphertext[500];
    int i, c, p;

    printf("Enter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("\nDecrypted text:\n");

    for(i = 0; ciphertext[i] != '\0'; i++)
    {
        if(ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
        {
            c = ciphertext[i] - 'A';

            /* Decryption: P = 5(C - 7) mod 26 */
            p = (5 * (c - 7)) % 26;

            if(p < 0)
                p += 26;

            printf("%c", p + 'A');
        }
        else if(ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
        {
            c = ciphertext[i] - 'a';

            p = (5 * (c - 7)) % 26;

            if(p < 0)
                p += 26;

            printf("%c", p + 'a');
        }
        else
        {
            printf("%c", ciphertext[i]);
        }
    }

    return 0;
}