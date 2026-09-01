#include <stdio.h>

long long powerMod(long long a, long long e, long long n)
{
    long long result = 1;

    while(e > 0)
    {
        if(e % 2 == 1)
            result = (result * a) % n;

        a = (a * a) % n;
        e = e / 2;
    }

    return result;
}

int main()
{
    long long n = 3233;
    long long e = 17;

    int i;

    printf("RSA Codebook Attack\n\n");

    printf("Encrypted alphabet:\n");

    for(i = 0; i < 26; i++)
    {
        printf("%c -> %lld\n",
               'A' + i,
               powerMod(i, e, n));
    }

    printf("\nAttack:\n");
    printf("Encrypt all 26 possible letters.\n");
    printf("Compare ciphertext with the table.\n");
    printf("Therefore individual-character RSA is insecure.\n");

    return 0;
}