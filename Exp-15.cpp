#include <stdio.h>
#include <string.h>
#include <ctype.h>

double englishFreq[26] =
{
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

double score(char text[])
{
    int count[26] = {0};
    int total = 0;
    int i;
    double chi = 0;

    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            count[toupper(text[i]) - 'A']++;
            total++;
        }
    }

    for(i = 0; i < 26; i++)
    {
        double expected = total * englishFreq[i] / 100.0;

        if(expected > 0)
            chi += ((count[i] - expected) *
                    (count[i] - expected)) / expected;
    }

    return chi;
}

void decrypt(char cipher[], char plain[], int key)
{
    int i;

    for(i = 0; cipher[i] != '\0'; i++)
    {
        if(cipher[i] >= 'A' && cipher[i] <= 'Z')
            plain[i] = ((cipher[i] - 'A' - key + 26) % 26) + 'A';

        else if(cipher[i] >= 'a' && cipher[i] <= 'z')
            plain[i] = ((cipher[i] - 'a' - key + 26) % 26) + 'a';

        else
            plain[i] = cipher[i];
    }

    plain[i] = '\0';
}

int main()
{
    char cipher[500];
    char plain[500];

    printf("Enter ciphertext:\n");
    fgets(cipher, sizeof(cipher), stdin);

    printf("\nPossible plaintexts:\n\n");

    /* Try all 26 keys */
    int key;

    for(key = 0; key < 26; key++)
    {
        decrypt(cipher, plain, key);

        printf("Key %2d : %s", key, plain);
        printf("Score  : %.2f\n\n", score(plain));
    }

    return 0;
}