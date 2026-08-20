#include <stdio.h>
#include <string.h>

int main()
{
    char ciphertext[1000];
    char cipher[100];
    char plain[100];
    int i, j, found;

    printf("Enter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("\nEnter number of substitutions: ");
    int n;
    scanf("%d", &n);

    printf("\nEnter substitution pairs.\n");
    printf("Example: ciphertext symbol followed by plaintext letter\n\n");

    for(i = 0; i < n; i++)
    {
        printf("Pair %d: ", i + 1);
        scanf(" %c %c", &cipher[i], &plain[i]);
    }

    printf("\nDecrypted message:\n");

    for(i = 0; ciphertext[i] != '\0'; i++)
    {
        found = 0;

        for(j = 0; j < n; j++)
        {
            if(ciphertext[i] == cipher[j])
            {
                printf("%c", plain[j]);
                found = 1;
                break;
            }
        }

        if(!found)
            printf("%c", ciphertext[i]);
    }

    return 0;
}