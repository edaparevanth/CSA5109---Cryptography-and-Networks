#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] =
{
    {'M','F','H','I','K'},
    {'U','N','O','P','Q'},
    {'Z','V','W','X','Y'},
    {'E','L','A','R','G'},
    {'D','S','T','B','C'}
};

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
    char message[200];
    char text[200];
    int i, len = 0;
    int r1, c1, r2, c2;

    printf("Enter message:\n");
    fgets(message, sizeof(message), stdin);

    /* Remove spaces and punctuation */
    for (i = 0; message[i] != '\0'; i++)
    {
        if (isalpha(message[i]))
        {
            char ch = toupper(message[i]);

            if (ch == 'J')
                ch = 'I';

            text[len++] = ch;
        }
    }

    text[len] = '\0';

    /* Add X if length is odd */
    if (len % 2 != 0)
        text[len++] = 'X';

    printf("\nPrepared plaintext: %s", text);
    printf("\nCiphertext: ");

    for (i = 0; i < len; i += 2)
    {
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        /* Same row */
        if (r1 == r2)
        {
            printf("%c", matrix[r1][(c1 + 1) % 5]);
            printf("%c", matrix[r2][(c2 + 1) % 5]);
        }

        /* Same column */
        else if (c1 == c2)
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