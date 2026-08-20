#include <stdio.h>
#include <stdint.h>

int shifts[16] =
{
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

uint32_t rotate28(uint32_t x, int n)
{
    x &= 0x0FFFFFFF;

    return ((x << n) |
            (x >> (28 - n))) & 0x0FFFFFFF;
}

int main()
{
    uint32_t C, D;
    int i;

    printf("Enter C0 (28-bit hexadecimal): ");
    scanf("%x", &C);

    printf("Enter D0 (28-bit hexadecimal): ");
    scanf("%x", &D);

    C &= 0x0FFFFFFF;
    D &= 0x0FFFFFFF;

    printf("\nDES Key Schedule:\n");

    for(i = 0; i < 16; i++)
    {
        C = rotate28(C, shifts[i]);
        D = rotate28(D, shifts[i]);

        printf("Round %2d: C = %07X  D = %07X\n",
               i + 1, C, D);
    }

    return 0;
}