#include <stdio.h>
#include <string.h>

char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void showCandidate(char cipher[], int keyShift)
{
    int i;
    char c;

    for(i=0;cipher[i]!='\0';i++)
    {
        if(cipher[i]>='A' && cipher[i]<='Z')
        {
            c = ((cipher[i]-'A'-keyShift+26)%26)+'A';
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

    int count[26]={0};
    int i;
    int top[10];

    printf("Enter ciphertext:\n");
    fgets(cipher,500,stdin);

    /* Count frequencies */
    for(i=0;cipher[i]!='\0';i++)
    {
        if(cipher[i]>='A' && cipher[i]<='Z')
            count[cipher[i]-'A']++;
    }

    printf("\nEnglish frequency order:\n");
    printf("%s\n",english);

    printf("\nTop 10 candidate plaintexts:\n\n");

    /*
       Try the 26 possible Caesar shifts as basic
       frequency-analysis candidates.
    */

    for(i=0;i<10;i++)
    {
        top[i]=i;
        printf("Candidate %d: ",i+1);
        showCandidate(cipher,i);
    }

    printf("\nFrequency counts:\n");

    for(i=0;i<26;i++)
    {
        printf("%c = %d\n",'A'+i,count[i]);
    }

    return 0;
}