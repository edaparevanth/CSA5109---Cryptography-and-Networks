#include <stdio.h>

int encrypt(int x, int key)
{
    return x ^ key;
}

int main()
{
    int X = 25;
    int K = 123;

    int T;
    int X2;
    int C2;

    printf("CBC-MAC Forgery Demonstration\n\n");

    /* One block MAC */
    T = encrypt(X, K);

    printf("X = %d\n", X);
    printf("K = %d\n", K);
    printf("T = MAC(K,X) = %d\n", T);

    /* Second block */
    X2 = X ^ T;

    printf("\nConstructed second block:\n");
    printf("X XOR T = %d\n", X2);

    /* CBC second encryption */
    C2 = encrypt(X2 ^ T, K);

    printf("\nMAC of X || (X XOR T): %d\n", C2);

    if(C2 == T)
        printf("\nForgery successful!\n");
    else
        printf("\nForgery failed.\n");

    return 0;
}