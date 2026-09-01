#include <stdio.h>

long long powerMod(long long base, long long exp, long long mod)
{
    long long result = 1;

    while(exp > 0)
    {
        if(exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main()
{
    long long q = 23;
    long long a = 5;

    long long x = 6;   /* Alice secret */
    long long y = 15;  /* Bob secret */

    long long A, B;
    long long keyAlice, keyBob;

    printf("DIFFIE-HELLMAN KEY EXCHANGE\n\n");

    printf("Public q = %lld\n", q);
    printf("Public a = %lld\n\n", a);

    A = powerMod(a, x, q);
    B = powerMod(a, y, q);

    printf("Alice sends A = %lld\n", A);
    printf("Bob sends B   = %lld\n\n", B);

    keyAlice = powerMod(B, x, q);
    keyBob = powerMod(A, y, q);

    printf("Alice key = %lld\n", keyAlice);
    printf("Bob key   = %lld\n", keyBob);

    if(keyAlice == keyBob)
        printf("\nShared secret established!\n");
    else
        printf("\nKey exchange failed.\n");

    printf("\nIf x^a and y^a are sent instead,\n");
    printf("normal Diffie-Hellman key agreement does not work.\n");

    return 0;
}