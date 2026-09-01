#include <stdio.h>

int main()
{
    int a, b;
    int p;
    int c;

    printf("Enter a: ");
    scanf("%d",&a);

    printf("Enter b: ");
    scanf("%d",&b);

    printf("\nAffine Cipher Table:\n");

    for(p=0;p<26;p++)
    {
        c=(a*p+b)%26;

        printf("%c -> %c\n",
               'A'+p,
               'A'+c);
    }

    printf("\nChecking one-to-one property...\n");

    if(a==2 && b==3)
    {
        printf("E(0)  = %d\n",(a*0+b)%26);
        printf("E(13) = %d\n",(a*13+b)%26);

        printf("Both are equal.\n");
        printf("Therefore encryption is NOT one-to-one.\n");
    }

    if(a%2==0 || a%13==0)
        printf("\nWarning: a has no inverse modulo 26.\n");
    else
        printf("\nThis value of a can be invertible modulo 26.\n");

    return 0;
}