#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void xorBlock(unsigned char *a, unsigned char *b,
              unsigned char *result)
{
    int i;

    for(i = 0; i < BLOCK_SIZE; i++)
        result[i] = a[i] ^ b[i];
}


void encryptBlock(unsigned char *input,
                 unsigned char *output,
                 unsigned char *key)
{
    int i;

    for(i = 0; i < BLOCK_SIZE; i++)
    {
        output[i] = input[i] ^ key[i];

        output[i] = (output[i] << 1) |
                    (output[i] >> 7);
    }
}

int main()
{
    unsigned char plaintext[100];
    unsigned char ciphertext[100];
    unsigned char previous[BLOCK_SIZE];
    unsigned char temp[BLOCK_SIZE];
    unsigned char block[BLOCK_SIZE];

    unsigned char key[BLOCK_SIZE] =
    {
        0x13, 0x34, 0x57, 0x79,
        0x9B, 0xBC, 0xDF, 0xF1
    };

    int length;
    int paddedLength;
    int i, j;

    printf("Enter plaintext: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);


    length = strlen((char *)plaintext);

    if(plaintext[length - 1] == '\n')
    {
        plaintext[length - 1] = '\0';
        length--;
    }


    paddedLength = ((length + 7) / 8) * 8;

    for(i = length; i < paddedLength; i++)
        plaintext[i] = 0;

    unsigned char iv[BLOCK_SIZE] =
    {
        0x12, 0x34, 0x56, 0x78,
        0x90, 0xAB, 0xCD, 0xEF
    };

    memcpy(previous, iv, BLOCK_SIZE);

    printf("\nPlaintext : %s\n", plaintext);


    for(i = 0; i < paddedLength; i += BLOCK_SIZE)
    {
        for(j = 0; j < BLOCK_SIZE; j++)
            block[j] = plaintext[i + j];

        xorBlock(block, previous, temp);

        encryptBlock(temp, &ciphertext[i], key);

        for(j = 0; j < BLOCK_SIZE; j++)
            previous[j] = ciphertext[i + j];
    }

    printf("Ciphertext: ");

    for(i = 0; i < paddedLength; i++)
        printf("%02X ", ciphertext[i]);

    printf("\n");

    return 0;
}