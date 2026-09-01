#include <stdio.h>
#include <string.h>

int main()
{
    char plaintext[100];
    int blockSize = 8;
    int len, padding, i;

    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    len = strlen(plaintext);

    padding = blockSize - (len % blockSize);

    if (padding == 0)
        padding = blockSize;

    printf("\nOriginal plaintext: %s", plaintext);
    printf("\nOriginal length: %d", len);

    printf("\nPadding: 1");

    for (i = 1; i < padding; i++)
        printf("0");

    printf("\nTotal padding = %d bits", padding);

    printf("\n\nReason for adding a padding block even when");
    printf("\nthe message is already complete:");
    printf("\nIt makes padding removal unambiguous.");

    return 0;
}