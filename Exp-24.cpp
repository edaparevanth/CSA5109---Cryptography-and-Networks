#include <stdio.h>

int gcd(int a, int b)
{
    int temp;

    while(b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

int main()
{
    int n;
    int m;
    int factor;

    printf("Enter RSA modulus n: ");
    scanf("%d", &n);

    printf("Enter known plaintext block m: ");
    scanf("%d", &m);

    factor = gcd(m, n);

    printf("\nGCD(m,n) = %d\n", factor);

    if(factor > 1 && factor < n)
    {
        printf("\nA factor of n is found!\n");
        printf("p = %d\n", factor);
        printf("q = %d\n", n / factor);

        printf("\nRSA modulus has been factored.\n");
        printf("Therefore the RSA system is compromised.\n");
    }
    else
    {
        printf("\nNo non-trivial common factor found.\n");
    }

    return 0;
}