#include <stdio.h>

int modInverse(int a)
{
    int i;

    for(i=1;i<26;i++)
    {
        if((a*i)%26==1)
            return i;
    }

    return -1;
}

int main()
{
    /*
       Plaintext:
       HI -> H=7, I=8
       AT -> A=0, T=19

       Ciphertext:
       TC -> T=19, C=2
       GK -> G=6, K=10
    */

    int P[2][2]={
        {7,0},
        {8,19}
    };

    int C[2][2]={
        {19,6},
        {2,10}
    };

    int det;
    int inv;
    int K[2][2];

    det=(P[0][0]*P[1][1]-P[0][1]*P[1][0])%26;

    if(det<0)
        det+=26;

    inv=modInverse(det);

    if(inv==-1)
    {
        printf("Matrix cannot be inverted modulo 26.\n");
        return 0;
    }

    /*
       P inverse =
       inv(det) * [d -b; -c a]
    */

    int Pinv[2][2];

    Pinv[0][0]=( P[1][1]*inv)%26;
    Pinv[0][1]=(-P[0][1]*inv)%26;
    Pinv[1][0]=(-P[1][0]*inv)%26;
    Pinv[1][1]=( P[0][0]*inv)%26;

    int i,j,k;

    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            K[i][j]=0;

            for(k=0;k<2;k++)
                K[i][j]+=C[i][k]*Pinv[k][j];

            K[i][j]%=26;

            if(K[i][j]<0)
                K[i][j]+=26;
        }
    }

    printf("Hill Cipher Known Plaintext Attack\n\n");

    printf("Recovered key matrix:\n");

    printf("%d %d\n",K[0][0],K[0][1]);
    printf("%d %d\n",K[1][0],K[1][1]);

    printf("\nKnown plaintext provides enough information\n");
    printf("to recover the encryption matrix.\n");

    return 0;
}