#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char keyword[50];
    char cipher[26];
    char plaintext[200];
    int used[26] = {0};
    int i, j = 0;
    char ch;

    printf("Enter keyword: ");
    scanf("%s", keyword);

    /* Create cipher alphabet using keyword */
    for(i = 0; keyword[i] != '\0'; i++)
    {
        ch = toupper(keyword[i]);

        if(ch >= 'A' && ch <= 'Z' && used[ch - 'A'] == 0)
        {
            cipher[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    /* Add remaining unused letters */
    for(ch = 'A'; ch <= 'Z'; ch++)
    {
        if(used[ch - 'A'] == 0)
        {
            cipher[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    cipher[26] = '\0';

    printf("\nPlain alphabet : ");
    for(i = 0; i < 26; i++)
        printf("%c ", 'A' + i);

    printf("\nCipher alphabet: ");
    for(i = 0; i < 26; i++)
        printf("%c ", cipher[i]);

    printf("\n\nEnter plaintext: ");
    getchar();
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("\nCiphertext: ");

    for(i = 0; plaintext[i] != '\0'; i++)
    {
        if(plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            printf("%c", cipher[plaintext[i] - 'A']);
        }
        else if(plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            printf("%c", cipher[plaintext[i] - 'a']);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    return 0;
}