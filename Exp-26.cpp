#include <stdio.h>

int gcd(int a, int b)
{
    while(b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int modInverse(int e, int phi)
{
    int d;

    for(d = 1; d < phi; d++)
    {
        if((e * d) % phi == 1)
            return d;
    }

    return -1;
}

int main()
{
    int p = 61;
    int q = 53;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int oldE = 17;
    int oldD = modInverse(oldE, phi);

    int newE = 7;
    int newD = modInverse(newE, phi);

    printf("RSA KEY CHANGE\n\n");

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("n = %d\n", n);
    printf("phi(n) = %d\n\n", phi);

    printf("Old public key  = (%d,%d)\n", oldE, n);
    printf("Old private key = (%d,%d)\n\n", oldD, n);

    printf("New public key  = (%d,%d)\n", newE, n);
    printf("New private key = (%d,%d)\n\n", newD, n);

    printf("Is it safe? NO\n");
    printf("The modulus n is still the same.\n");
    printf("A new modulus with new primes should be generated.\n");

    return 0;
}