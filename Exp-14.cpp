#include <stdio.h>
#include <string.h>

int main()
{
    char ciphertext[] = "BJOUYFJCMZQCW";
    char plaintext[]  = "CASHNOTNEEDED";

    int i;
    int key[100];

    printf("Ciphertext : %s\n", ciphertext);
    printf("Plaintext  : %s\n", plaintext);

    printf("\nRequired key: ");

    for(i = 0; ciphertext[i] != '\0'; i++)
    {
        int c = ciphertext[i] - 'A';
        int p = plaintext[i] - 'A';

        key[i] = (c - p + 26) % 26;

        printf("%d ", key[i]);
    }

    printf("\n");

    return 0;
}