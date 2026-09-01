#include <stdio.h>

int main()
{
    int stateLanes = 25;
    int blockSize = 1024;
    int laneSize = 64;

    int rateLanes;
    int capacityLanes;

    int i;

    rateLanes = blockSize / laneSize;
    capacityLanes = stateLanes - rateLanes;

    printf("SHA-3 Lane Analysis\n\n");

    printf("State size       = 1600 bits\n");
    printf("Block size       = %d bits\n", blockSize);
    printf("Lane size        = %d bits\n", laneSize);

    printf("Rate lanes       = %d\n", rateLanes);
    printf("Capacity lanes   = %d\n", capacityLanes);

    printf("\nInitial capacity lanes:\n");

    for(i = 0; i < capacityLanes; i++)
        printf("Lane %d = 0\n", i + 1);

    printf("\nPermutation is ignored as specified.\n");
    printf("Therefore capacity lanes remain zero.\n");
    printf("They will NEVER become nonzero.\n");

    return 0;
}