#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 4
#define NUM_BLOCKS 4

/*
    Simple educational encryption function.
    This is NOT a real cryptographic algorithm.
    It is used only to demonstrate error propagation.
*/
void encryptBlock(unsigned char *plain,
                  unsigned char *cipher)
{
    int i;

    for(i = 0; i < BLOCK_SIZE; i++)
    {
        cipher[i] = plain[i] ^ 0xAA;
    }
}

/*
    Simple decryption function.
*/
void decryptBlock(unsigned char *cipher,
                  unsigned char *plain)
{
    int i;

    for(i = 0; i < BLOCK_SIZE; i++)
    {
        plain[i] = cipher[i] ^ 0xAA;
    }
}

/* ECB Encryption */
void ecbEncrypt(unsigned char plain[][BLOCK_SIZE],
                unsigned char cipher[][BLOCK_SIZE])
{
    int i;

    for(i = 0; i < NUM_BLOCKS; i++)
    {
        encryptBlock(plain[i], cipher[i]);
    }
}

/* ECB Decryption */
void ecbDecrypt(unsigned char cipher[][BLOCK_SIZE],
                unsigned char plain[][BLOCK_SIZE])
{
    int i;

    for(i = 0; i < NUM_BLOCKS; i++)
    {
        decryptBlock(cipher[i], plain[i]);
    }
}

/* CBC Encryption */
void cbcEncrypt(unsigned char plain[][BLOCK_SIZE],
                unsigned char cipher[][BLOCK_SIZE],
                unsigned char iv[])
{
    int i, j;
    unsigned char temp[BLOCK_SIZE];

    for(i = 0; i < NUM_BLOCKS; i++)
    {
        for(j = 0; j < BLOCK_SIZE; j++)
        {
            if(i == 0)
                temp[j] = plain[i][j] ^ iv[j];
            else
                temp[j] = plain[i][j] ^ cipher[i-1][j];
        }

        encryptBlock(temp, cipher[i]);
    }
}

/* CBC Decryption */
void cbcDecrypt(unsigned char cipher[][BLOCK_SIZE],
                unsigned char plain[][BLOCK_SIZE],
                unsigned char iv[])
{
    int i, j;
    unsigned char temp[BLOCK_SIZE];

    for(i = 0; i < NUM_BLOCKS; i++)
    {
        decryptBlock(cipher[i], temp);

        for(j = 0; j < BLOCK_SIZE; j++)
        {
            if(i == 0)
                plain[i][j] = temp[j] ^ iv[j];
            else
                plain[i][j] = temp[j] ^ cipher[i-1][j];
        }
    }
}

void display(unsigned char data[][BLOCK_SIZE])
{
    int i, j;

    for(i = 0; i < NUM_BLOCKS; i++)
    {
        printf("P%d/C%d: ", i + 1, i + 1);

        for(j = 0; j < BLOCK_SIZE; j++)
            printf("%02X ", data[i][j]);

        printf("\n");
    }
}

int main()
{
    unsigned char plain[NUM_BLOCKS][BLOCK_SIZE] =
    {
        {'A','B','C','D'},
        {'E','F','G','H'},
        {'I','J','K','L'},
        {'M','N','O','P'}
    };

    unsigned char ecbCipher[NUM_BLOCKS][BLOCK_SIZE];
    unsigned char ecbRecovered[NUM_BLOCKS][BLOCK_SIZE];

    unsigned char cbcCipher[NUM_BLOCKS][BLOCK_SIZE];
    unsigned char cbcRecovered[NUM_BLOCKS][BLOCK_SIZE];

    unsigned char iv[BLOCK_SIZE] =
    {
        1, 2, 3, 4
    };

    int i;

    printf("Original Plaintext Blocks:\n");

    for(i = 0; i < NUM_BLOCKS; i++)
    {
        printf("P%d: ", i + 1);

        for(int j = 0; j < BLOCK_SIZE; j++)
            printf("%c ", plain[i][j]);

        printf("\n");
    }

    /* ---------------- ECB ---------------- */

    ecbEncrypt(plain, ecbCipher);

    printf("\nECB Ciphertext:\n");
    display(ecbCipher);

    /*
       Introduce an error into C1
    */
    ecbCipher[0][0] ^= 0x01;

    ecbDecrypt(ecbCipher, ecbRecovered);

    printf("\nECB after error in C1:\n");
    display(ecbRecovered);

    /* ---------------- CBC ---------------- */

    cbcEncrypt(plain, cbcCipher, iv);

    printf("\nCBC Ciphertext:\n");
    display(cbcCipher);

    /*
       Introduce an error into C1
    */
    cbcCipher[0][0] ^= 0x01;

    cbcDecrypt(cbcCipher, cbcRecovered, iv);

    printf("\nCBC after error in C1:\n");
    display(cbcRecovered);

    return 0;
}