#include <stdio.h>

int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int IP[]  = {2,6,3,1,4,8,5,7};
int IP_INV[] = {4,1,3,5,7,2,8,6};
int EP[] = {4,1,2,3,2,3,4,1};
int P4[] = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

int key1[8], key2[8];

void permute(int *input, int *output, int *table, int n)
{
    int i;

    for(i = 0; i < n; i++)
        output[i] = input[table[i] - 1];
}

void leftShift(int *bits, int n)
{
    int temp, i;

    temp = bits[0];

    for(i = 0; i < n - 1; i++)
        bits[i] = bits[i + 1];

    bits[n - 1] = temp;
}

void generateKeys(int key[10])
{
    int temp[10], left[5], right[5];
    int i;

    permute(key, temp, P10, 10);

    for(i = 0; i < 5; i++)
    {
        left[i] = temp[i];
        right[i] = temp[i + 5];
    }

    leftShift(left, 5);
    leftShift(right, 5);

    for(i = 0; i < 5; i++)
    {
        temp[i] = left[i];
        temp[i + 5] = right[i];
    }

    permute(temp, key1, P8, 8);

    leftShift(left, 5);
    leftShift(left, 5);

    leftShift(right, 5);
    leftShift(right, 5);

    for(i = 0; i < 5; i++)
    {
        temp[i] = left[i];
        temp[i + 5] = right[i];
    }

    permute(temp, key2, P8, 8);
}

void XOR(int *a, int *b, int *result, int n)
{
    int i;

    for(i = 0; i < n; i++)
        result[i] = a[i] ^ b[i];
}

void fk(int *bits, int *key)
{
    int left[4], right[4];
    int ep[8], x[8], p4[4];
    int s0out[2], s1out[2];
    int row, col, value;
    int i;

    for(i = 0; i < 4; i++)
    {
        left[i] = bits[i];
        right[i] = bits[i + 4];
    }

    permute(right, ep, EP, 8);

    XOR(ep, key, x, 8);

    row = x[0] * 2 + x[3];
    col = x[1] * 2 + x[2];

    value = S0[row][col];

    s0out[0] = value / 2;
    s0out[1] = value % 2;

    row = x[4] * 2 + x[7];
    col = x[5] * 2 + x[6];

    value = S1[row][col];

    s1out[0] = value / 2;
    s1out[1] = value % 2;

    int temp[4];

    temp[0] = s0out[0];
    temp[1] = s0out[1];
    temp[2] = s1out[0];
    temp[3] = s1out[1];

    permute(temp, p4, P4, 4);

    for(i = 0; i < 4; i++)
        bits[i] = left[i] ^ p4[i];
}

void switchBits(int *bits)
{
    int i, temp;

    for(i = 0; i < 4; i++)
    {
        temp = bits[i];
        bits[i] = bits[i + 4];
        bits[i + 4] = temp;
    }
}

void encryptSDES(int input[8], int output[8])
{
    int temp[8];
    int i;

    permute(input, temp, IP, 8);

    fk(temp, key1);

    switchBits(temp);

    fk(temp, key2);

    permute(temp, output, IP_INV, 8);
}

void decryptSDES(int input[8], int output[8])
{
    int temp[8];

    permute(input, temp, IP, 8);

    fk(temp, key2);

    switchBits(temp);

    fk(temp, key1);

    permute(temp, output, IP_INV, 8);
}

void intToBits(int value, int bits[8])
{
    int i;

    for(i = 7; i >= 0; i--)
    {
        bits[i] = value % 2;
        value = value / 2;
    }
}

int bitsToInt(int bits[8])
{
    int value = 0;
    int i;

    for(i = 0; i < 8; i++)
        value = value * 2 + bits[i];

    return value;
}

void printBinary(int value)
{
    int i;

    for(i = 7; i >= 0; i--)
        printf("%d", (value >> i) & 1);
}

int main()
{
    int key[10] = {0,1,1,1,1,1,1,1,0,1};

    int plaintext[2] = {0x01, 0x23};
    int ciphertext[2];
    int decrypted[2];

    int iv = 0xAA;

    int input[8], output[8];
    int i;

    generateKeys(key);

    printf("S-DES CBC MODE\n\n");

    printf("Key       : 0111111101\n");
    printf("IV        : ");
    printBinary(iv);
    printf("\n");

    printf("Plaintext : ");
    printBinary(plaintext[0]);
    printf(" ");
    printBinary(plaintext[1]);
    printf("\n");

    /* CBC Encryption */
    for(i = 0; i < 2; i++)
    {
        int value;

        if(i == 0)
            value = plaintext[i] ^ iv;
        else
            value = plaintext[i] ^ ciphertext[i - 1];

        intToBits(value, input);

        encryptSDES(input, output);

        ciphertext[i] = bitsToInt(output);
    }

    printf("\nCiphertext: ");

    for(i = 0; i < 2; i++)
    {
        printBinary(ciphertext[i]);
        printf(" ");
    }

    printf("\n");

    /* CBC Decryption */
    for(i = 0; i < 2; i++)
    {
        int value;

        intToBits(ciphertext[i], input);

        decryptSDES(input, output);

        value = bitsToInt(output);

        if(i == 0)
            decrypted[i] = value ^ iv;
        else
            decrypted[i] = value ^ ciphertext[i - 1];
    }

    printf("Decrypted : ");

    for(i = 0; i < 2; i++)
    {
        printBinary(decrypted[i]);
        printf(" ");
    }

    printf("\n");

    return 0;
}