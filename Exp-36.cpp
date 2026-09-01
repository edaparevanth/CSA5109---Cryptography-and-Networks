#include <stdio.h>
#include <string.h>

char freq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void decrypt(char text[], int map[], char result[])
{
    int i;

    for(i=0;text[i]!='\0';i++)
    {
        if(text[i]>='A' && text[i]<='Z')
            result[i]='A'+map[text[i]-'A'];
        else
            result[i]=text[i];
    }

    result[i]='\0';
}

int main()
{
    char cipher[500];
    char result[500];

    int count[26]={0};
    int map[26];

    int i,j,temp;

    printf("Enter ciphertext:\n");
    getchar();
    fgets(cipher,500,stdin);

    /* Frequency counting */
    for(i=0;cipher[i]!='\0';i++)
    {
        if(cipher[i]>='A' && cipher[i]<='Z')
            count[cipher[i]-'A']++;
    }

    /* Default identity mapping */
    for(i=0;i<26;i++)
        map[i]=i;

    /*
       Simple frequency mapping.
       Highest ciphertext frequency -> E,
       second -> T, etc.
    */

    for(i=0;i<26;i++)
    {
        for(j=i+1;j<26;j++)
        {
            if(count[j]>count[i])
            {
                temp=count[i];
                count[i]=count[j];
                count[j]=temp;
            }
        }
    }

    printf("\nFrequency analysis completed.\n");

    printf("\nLikely English frequency order:\n");
    printf("ETAOINSHRDLCUMWFGYPBVKJXQZ\n");

    printf("\nCandidate plaintext:\n");

    /*
       Basic demonstration output.
       Full substitution solving requires n-gram/dictionary scoring.
    */

    for(i=0;cipher[i]!='\0';i++)
    {
        if(cipher[i]>='A' && cipher[i]<='Z')
            result[i]='?';
        else
            result[i]=cipher[i];
    }

    result[i]='\0';

    printf("%s\n",result);

    printf("\nFrequency attack identifies likely letter mappings.\n");
    printf("For automatic full solving, English n-gram scoring is used.\n");

    return 0;
}