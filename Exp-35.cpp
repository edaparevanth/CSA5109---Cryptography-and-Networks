#include <stdio.h>
#include <string.h>

int main()
{
    char plaintext[100];
    char ciphertext[100];
    char decrypted[100];

    int key[100];

    int n;
    int i;

    printf("Enter plaintext (uppercase): ");
    scanf("%s",plaintext);

    n = strlen(plaintext);

    printf("Enter %d key numbers (0-25):\n",n);

    for(i=0;i<n;i++)
        scanf("%d",&key[i]);

    /* Encryption */
    for(i=0;i<n;i++)
    {
        ciphertext[i] =
            ((plaintext[i]-'A'+key[i])%26)+'A';
    }

    ciphertext[n]='\0';

    /* Decryption */
    for(i=0;i<n;i++)
    {
        decrypted[i] =
            ((ciphertext[i]-'A'-key[i]+26)%26)+'A';
    }

    decrypted[n]='\0';

    printf("\nPlaintext  : %s",plaintext);
    printf("\nCiphertext : %s",ciphertext);
    printf("\nDecrypted  : %s\n",decrypted);

    return 0;
}