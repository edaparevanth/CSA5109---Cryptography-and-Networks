#include <stdio.h>
#include <string.h>

int main()
{
    char plaintext[100];
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char ciphertext[100];
    int i;

    printf("Enter plaintext: ");
    gets(plaintext);

    for(i = 0; plaintext[i] != '\0'; i++)
    {
        if(plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            ciphertext[i] = key[plaintext[i] - 'A'];

        else if(plaintext[i] >= 'a' && plaintext[i] <= 'z')
            ciphertext[i] = key[plaintext[i] - 'a'];

        else
            ciphertext[i] = plaintext[i];
    }

    ciphertext[i] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}