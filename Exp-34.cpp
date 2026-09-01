#include <stdio.h>
#include <string.h>

void pad(char *data)
{
    int len = strlen(data);
    int block = 8;
    int padBytes = block - (len % block);

    if(padBytes == 0)
        padBytes = block;

    printf("\nOriginal data: %s", data);
    printf("\nPadding added: ");

    printf("1");

    int i;

    for(i=1;i<padBytes;i++)
        printf("0");

    printf("\nPadding size = %d\n", padBytes);

    printf("\nReason:\n");
    printf("A complete padding block makes the end of the\n");
    printf("message unambiguous during decryption.\n");
}

int main()
{
    char data[100];

    printf("Enter plaintext: ");
    scanf("%s",data);

    pad(data);

    return 0;
}