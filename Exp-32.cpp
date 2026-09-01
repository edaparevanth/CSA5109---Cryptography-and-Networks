#include <stdio.h>

long long powerMod(long long a, long long b, long long m)
{
    long long result = 1;

    while(b > 0)
    {
        if(b % 2 == 1)
            result = (result * a) % m;

        a = (a * a) % m;
        b = b / 2;
    }

    return result;
}

int main()
{
    long long p = 23;
    long long q = 11;
    long long g = 4;

    long long x = 3;       /* Private key */
    long long h = 7;       /* Message hash */

    long long k1 = 2;
    long long k2 = 5;

    long long r1, r2;
    long long s1, s2;
    long long y;

    y = powerMod(g, x, p);

    r1 = powerMod(g, k1, p) % q;
    r2 = powerMod(g, k2, p) % q;

    /* Simplified demonstration */
    s1 = ((h + x * r1) / k1) % q;
    s2 = ((h + x * r2) / k2) % q;

    printf("DSA Signature Demonstration\n\n");

    printf("Public key y = %lld\n", y);
    printf("Message hash = %lld\n\n", h);

    printf("First signing:\n");
    printf("k = %lld\n", k1);
    printf("Signature = (%lld, %lld)\n", r1, s1);

    printf("\nSecond signing:\n");
    printf("k = %lld\n", k2);
    printf("Signature = (%lld, %lld)\n", r2, s2);

    printf("\nSame message, different k -> different signatures.\n");

    return 0;
}