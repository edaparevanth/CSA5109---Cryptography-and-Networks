#include <stdio.h>
#include <string.h>

void decrypt(char cipher[], int key)
{
    int i;
    char c;

    for(i=0;cipher[i]!='\0';i++)
    {
        if(cipher[i]>='A' && cipher[i]<='Z')
        {
            c=((cipher[i]-'A'-key+26)%26)+'A';
            printf("%c",c);
        }
        else
        {
            printf("%c",cipher[i]);
        }
    }

    printf("\n");
}

int main()
{
    char cipher[500];
    int key;

    printf("Enter ciphertext in uppercase:\n");
    fgets(cipher,500,stdin);

    printf("\nPossible plaintexts:\n\n");

    for(key=0;key<26;key++)
    {
        printf("Key %2d : ",key);

        decrypt(cipher,key);
    }

    printf("\nThe correct plaintext can be selected using\n");
    printf("English frequency/language analysis.\n");

    return 0;
}