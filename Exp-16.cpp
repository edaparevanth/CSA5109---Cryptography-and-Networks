#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char common[] =
    "THE AND ING HER ERE ENT THA NTH WAS ETH FOR DTH "
    "HAT SHE ION TIO VER EST HIS OTH ONS RES NOT "
    "ARE ALL YOU BUT HAD ONE OUT OUR";

int scoreText(char text[])
{
    int score = 0;
    int i;

    for(i = 0; text[i + 3] != '\0'; i++)
    {
        char a = toupper(text[i]);
        char b = toupper(text[i + 1]);
        char c = toupper(text[i + 2]);

        if(a == 'T' && b == 'H' && c == 'E')
            score += 10;

        if(a == 'A' && b == 'N' && c == 'D')
            score += 8;

        if(a == 'I' && b == 'N' && c == 'G')
            score += 8;

        if(a == 'T' && b == 'I' && c == 'O')
            score += 6;

        if(a == 'E' && b == 'R' && c == 'E')
            score += 5;

        if(a == 'T' && b == 'H' && c == 'A')
            score += 5;

        if(a == 'H' && b == 'E' && c == 'R')
            score += 5;
    }

    return score;
}

void decrypt(char cipher[], char key[], char plain[])
{
    int i;

    for(i = 0; cipher[i] != '\0'; i++)
    {
        if(cipher[i] >= 'A' && cipher[i] <= 'Z')
            plain[i] = key[cipher[i] - 'A'];

        else if(cipher[i] >= 'a' && cipher[i] <= 'z')
            plain[i] = tolower(key[cipher[i] - 'a']);

        else
            plain[i] = cipher[i];
    }

    plain[i] = '\0';
}

void shuffle(char key[])
{
    int i, j;
    char temp;

    for(i = 25; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = key[i];
        key[i] = key[j];
        key[j] = temp;
    }
}

int main()
{
    char cipher[1000];
    char key[27];
    char bestKey[27];
    char plain[1000];

    int i, iteration;
    int bestScore = -1;

    srand((unsigned)time(NULL));

    printf("Enter ciphertext:\n");
    fgets(cipher, sizeof(cipher), stdin);

    for(i = 0; i < 26; i++)
        key[i] = 'A' + i;

    key[26] = '\0';

    for(iteration = 0; iteration < 10000; iteration++)
    {
        shuffle(key);

        decrypt(cipher, key, plain);

        int currentScore = scoreText(plain);

        if(currentScore > bestScore)
        {
            bestScore = currentScore;
            strcpy(bestKey, key);
        }
    }

    decrypt(cipher, bestKey, plain);

    printf("\nBest estimated plaintext:\n");
    printf("%s\n", plain);

    printf("\nEstimated substitution key:\n");
    printf("%s\n", bestKey);

    return 0;
}