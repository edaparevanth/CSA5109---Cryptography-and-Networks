#include <stdio.h>

int modInverse(int a)
{
    int i;

    a = a % 26;

    for (i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

int main()
{
    char p1[3], p2[3];
    char c1[3], c2[3];

    int P[2][2];
    int C[2][2];
    int InvP[2][2];
    int K[2][2];

    int det, invDet;

    printf("Enter first plaintext pair: ");
    scanf("%2s", p1);

    printf("Enter corresponding ciphertext pair: ");
    scanf("%2s", c1);

    printf("Enter second plaintext pair: ");
    scanf("%2s", p2);

    printf("Enter corresponding ciphertext pair: ");
    scanf("%2s", c2);

    /*
       P matrix:
       p1[0] p2[0]
       p1[1] p2[1]
    */

    P[0][0] = p1[0] - 'A';
    P[1][0] = p1[1] - 'A';

    P[0][1] = p2[0] - 'A';
    P[1][1] = p2[1] - 'A';

    /*
       C matrix
    */

    C[0][0] = c1[0] - 'A';
    C[1][0] = c1[1] - 'A';

    C[0][1] = c2[0] - 'A';
    C[1][1] = c2[1] - 'A';

    /* Determinant of P */

    det = (P[0][0] * P[1][1] -
           P[0][1] * P[1][0]) % 26;

    if (det < 0)
        det += 26;

    invDet = modInverse(det);

    if (invDet == -1)
    {
        printf("Plaintext matrix has no inverse modulo 26.\n");
        return 0;
    }

    /* Inverse of P */

    InvP[0][0] = ( invDet * P[1][1]) % 26;
    InvP[0][1] = (-invDet * P[0][1]) % 26;
    InvP[1][0] = (-invDet * P[1][0]) % 26;
    InvP[1][1] = ( invDet * P[0][0]) % 26;

    if (InvP[0][1] < 0)
        InvP[0][1] += 26;

    if (InvP[1][0] < 0)
        InvP[1][0] += 26;

    /* K = C * inverse(P) */

    K[0][0] = (C[0][0] * InvP[0][0] +
               C[0][1] * InvP[1][0]) % 26;

    K[0][1] = (C[0][0] * InvP[0][1] +
               C[0][1] * InvP[1][1]) % 26;

    K[1][0] = (C[1][0] * InvP[0][0] +
               C[1][1] * InvP[1][0]) % 26;

    K[1][1] = (C[1][0] * InvP[0][1] +
               C[1][1] * InvP[1][1]) % 26;

    printf("\nRecovered Hill Cipher Key:\n");

    printf("%d %d\n", K[0][0], K[0][1]);
    printf("%d %d\n", K[1][0], K[1][1]);

    return 0;
}