#include <stdio.h>
#include <stdint.h>

int shifts[16] =
{
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

uint32_t leftRotate28(uint32_t value, int shift)
{
    value &= 0x0FFFFFFF;

    return ((value << shift) |
            (value >> (28 - shift))) & 0x0FFFFFFF;
}

int main()
{
    uint32_t C, D;
    uint32_t subkey[16];

    int i;

    printf("Enter 28-bit C value in hexadecimal: ");
    scanf("%x", &C);

    printf("Enter 28-bit D value in hexadecimal: ");
    scanf("%x", &D);

    C &= 0x0FFFFFFF;
    D &= 0x0FFFFFFF;

    /* Generate encryption subkeys */
    for(i = 0; i < 16; i++)
    {
        C = leftRotate28(C, shifts[i]);
        D = leftRotate28(D, shifts[i]);

        /*
         * In a complete DES implementation,
         * PC-2 is applied here to generate 48-bit K.
         *
         * This example stores C and D together
         * to demonstrate the reverse schedule.
         */

        subkey[i] = C;
    }

    printf("\nDES decryption order:\n");

    for(i = 15; i >= 0; i--)
    {
        printf("K%d\n", i + 1);
    }

    printf("\nShift schedule:\n");

    for(i = 15; i >= 0; i--)
        printf("%d ", shifts[i]);

    printf("\n");

    return 0;
}