#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    int n, curNum=0;
    printf("Rozsah:\n");
    if (scanf("%d", &n) == 1 && n>0)
    {
        int largest = floor(log10(abs(n * n))) + 1;
        printf("%*s%s", largest, " ", "|");

        for (int i = n; i > 0; i--)
        {
            curNum = floor(log10(abs(i))) + 1;
            printf("%*s%d", largest - curNum + 1, " ", i);
        }
        printf("\n");
        for (int i = 0; i < largest - curNum + 1; i++)
        {
            printf("-");
        }
        printf("+");
        for (int i = 0; i < n * (largest + 1); i++)
        {
            printf("-");
        }
        printf("\n");
        for (int i = 1; i <= n; i++)
        {
            curNum = floor(log10(abs(i))) + 1;
            if (largest - curNum == 0)
            {
                printf("%d%s", i, "|");
            }
            else
            {
                printf("%*s%d%s", largest - curNum, " ", i, "|");
            }
            for (int o = n; o >= i; o--)
            {
                curNum = floor(log10(abs(i * o))) + 1;
                printf("%*s%d", largest - curNum + 1, " ", i * o);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Nespravny vstup.\n");
    }

    return 0;
}