#include <stdio.h>

int main()
{
    int P[4] = {10, 20, 30, 40};
    int C[4] = {11, 21, 31, 41};

    printf("Original plaintext blocks:\n");
    printf("P1=%d P2=%d P3=%d P4=%d\n", P[0], P[1], P[2], P[3]);

    printf("\nAfter error in transmitted C1:\n");

    printf("\nECB Mode:\n");
    printf("P1 = CORRUPTED\n");
    printf("P2 = %d\n", P[1]);
    printf("P3 = %d\n", P[2]);
    printf("P4 = %d\n", P[3]);

    printf("\nCBC Mode:\n");
    printf("P1 = CORRUPTED\n");
    printf("P2 = CORRUPTED at same bit position\n");
    printf("P3 = %d\n", P[2]);
    printf("P4 = %d\n", P[3]);

    printf("\nAnswers:\n");
    printf("a) No blocks beyond P2 are affected.\n");
    printf("b) Error in source P1 affects C1 only.\n");
    printf("   At receiver, P1 is corrupted; later blocks recover correctly.\n");

    return 0;
}