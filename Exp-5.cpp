#include <stdio.h>
#include <string.h>

int gcd(int a, int b)
{
    while(b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    char plaintext[100];
    int a, b, i;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    if(gcd(a, 26) != 1)
    {
        printf("Invalid value of a!\n");
        printf("a must be relatively prime to 26.\n");
        return 0;
    }

    printf("Ciphertext: ");

    for(i = 0; plaintext[i] != '\0'; i++)
    {
        if(plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            printf("%c", ((a * (plaintext[i] - 'A') + b) % 26) + 'A');
        }
        else if(plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            printf("%c", ((a * (plaintext[i] - 'a') + b) % 26) + 'a');
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    return 0;
}