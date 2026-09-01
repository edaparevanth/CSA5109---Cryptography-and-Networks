#include <stdio.h>

unsigned long long leftShift64(unsigned long long x)
{
    return x << 1;
}

unsigned long long generateK1_64(unsigned long long L)
{
    unsigned long long K1;

    K1 = L << 1;

    if(L & 0x8000000000000000ULL)
        K1 = K1 ^ 0x1B;

    return K1;
}

unsigned long long generateK2_64(unsigned long long K1)
{
    unsigned long long K2;

    K2 = K1 << 1;

    if(K1 & 0x8000000000000000ULL)
        K2 = K2 ^ 0x1B;

    return K2;
}

void print64(unsigned long long x)
{
    printf("%016llX", x);
}

int main()
{
    unsigned long long L;
    unsigned long long K1;
    unsigned long long K2;

    printf("CMAC SUBKEY GENERATION\n\n");

    printf("Enter L in hexadecimal (16 digits): ");
    scanf("%llX", &L);

    K1 = generateK1_64(L);
    K2 = generateK2_64(K1);

    printf("\nFor 64-bit block size:\n");
    printf("Rb = 1B\n");

    printf("L  = ");
    print64(L);

    printf("\nK1 = ");
    print64(K1);

    printf("\nK2 = ");
    print64(K2);

    printf("\n\nFor 128-bit block size:\n");
    printf("Rb = 87\n");

    printf("\nReason:\n");
    printf("Left shifting multiplies the polynomial by x.\n");
    printf("If the highest bit is 1, reduction is required.\n");
    printf("XOR with Rb performs this reduction.\n");

    return 0;
}