#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char key[])
{
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    for(i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);

        if(ch == 'J')
            ch = 'I';

        if(ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for(ch = 'A'; ch <= 'Z'; ch++)
    {
        if(ch == 'J')
            continue;

        if(!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if(ch == 'J')
        ch = 'I';

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

int main()
{
    char key[50], plaintext[100], prepared[200];
    char a, b;
    int i, len = 0;
    int r1, c1, r2, c2;

    printf("Enter keyword: ");
    gets(key);

    generateMatrix(key);

    printf("\nPlayfair Matrix:\n");

    for(i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);

        printf("\n");
    }

    printf("\nEnter plaintext: ");
    gets(plaintext);

    /* Prepare plaintext */
    for(i = 0; plaintext[i] != '\0'; i++)
    {
        if(isalpha(plaintext[i]))
        {
            a = toupper(plaintext[i]);

            if(a == 'J')
                a = 'I';

            prepared[len++] = a;
        }
    }

    prepared[len] = '\0';

    /* Insert X between repeated letters */
    for(i = 0; i < len - 1; i += 2)
    {
        if(prepared[i] == prepared[i + 1])
        {
            for(int j = len; j > i + 1; j--)
                prepared[j] = prepared[j - 1];

            prepared[i + 1] = 'X';
            len++;
        }
    }

    /* Add X if length is odd */
    if(len % 2 != 0)
        prepared[len++] = 'X';

    prepared[len] = '\0';

    printf("\nCiphertext: ");

    for(i = 0; i < len; i += 2)
    {
        findPosition(prepared[i], &r1, &c1);
        findPosition(prepared[i + 1], &r2, &c2);

        /* Same row */
        if(r1 == r2)
        {
            printf("%c", matrix[r1][(c1 + 1) % 5]);
            printf("%c", matrix[r2][(c2 + 1) % 5]);
        }

        /* Same column */
        else if(c1 == c2)
        {
            printf("%c", matrix[(r1 + 1) % 5][c1]);
            printf("%c", matrix[(r2 + 1) % 5][c2]);
        }

        /* Rectangle rule */
        else
        {
            printf("%c", matrix[r1][c2]);
            printf("%c", matrix[r2][c1]);
        }
    }

    return 0;
}