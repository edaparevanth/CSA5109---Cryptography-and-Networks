#include <stdio.h>

int gcdExtended(int a, int b, int *x, int *y)
{
    int x1, y1, g;

    if(b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    g = gcdExtended(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return g;
}

int main()
{
    int n = 3599;
    int e = 31;

    int p, q;
    int phi;
    int x, y;
    int d;

    /* Find p and q */
    for(p = 2; p <= n; p++)
    {
        if(n % p == 0)
        {
            q = n / p;
            break;
        }
    }

    phi = (p - 1) * (q - 1);

    gcdExtended(e, phi, &x, &y);

    d = x % phi;

    if(d < 0)
        d = d + phi;

    printf("RSA SYSTEM\n\n");

    printf("n = %d\n", n);
    printf("e = %d\n", e);

    printf("p = %d\n", p);
    printf("q = %d\n", q);

    printf("phi(n) = %d\n", phi);

    printf("Private key d = %d\n", d);

    printf("\nPublic Key  = (%d, %d)", e, n);
    printf("\nPrivate Key = (%d, %d)\n", d, n);

    return 0;
}