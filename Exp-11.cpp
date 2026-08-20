#include <stdio.h>
#include <math.h>

int main()
{
    double keys;
    double power;

    keys = tgamma(26);       /* 25! */
    power = log(keys) / log(2);

    printf("Number of possible Playfair keys = 25!\n");
    printf("25! = %.0f\n", keys);
    printf("Approximately = 2^%.2f\n", power);

    return 0;
}