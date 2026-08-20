#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plaintext[100];
    char key[100];
    char ciphertext[100];
    int i, j = 0;
    int shift;

    printf("Enter plaintext: ");
    gets(plaintext);

    printf("Enter key: ");
    gets(key);

    for(i = 0; plaintext[i] != '\0'; i++)
    {
        if(isalpha(plaintext[i]))
        {
            shift = toupper(key[j % strlen(key)]) - 'A';

            if(plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                ciphertext[i] =
                    ((plaintext[i] - 'A' + shift) % 26) + 'A';

            else
                ciphertext[i] =
                    ((plaintext[i] - 'a' + shift) % 26) + 'a';

            j++;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}