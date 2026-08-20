#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
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
    char ciphertext[300];
    int i;
    int r1, c1, r2, c2;

    printf("Enter 5x5 Playfair matrix:\n");

    for (i = 0; i < 5; i++)
        scanf("%s", matrix[i]);

    getchar();

    printf("\nEnter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("\nDecrypted text:\n");

    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char a = toupper(ciphertext[i]);

            while (ciphertext[i + 1] != '\0' &&
                   !isalpha(ciphertext[i + 1]))
                i++;

            i++;

            if (ciphertext[i] == '\0')
                break;

            char b = toupper(ciphertext[i]);

            findPosition(a, &r1, &c1);
            findPosition(b, &r2, &c2);

            /* Same row */
            if (r1 == r2)
            {
                printf("%c", matrix[r1][(c1 + 4) % 5]);
                printf("%c", matrix[r2][(c2 + 4) % 5]);
            }

            /* Same column */
            else if (c1 == c2)
            {
                printf("%c", matrix[(r1 + 4) % 5][c1]);
                printf("%c", matrix[(r2 + 4) % 5][c2]);
            }

            else
            {
                printf("%c", matrix[r1][c2]);
                printf("%c", matrix[r2][c1]);
            }
        }
    }

    return 0;
}