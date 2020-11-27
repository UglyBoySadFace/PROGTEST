#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(void)
{
    int x, y, input, result=0, done, interval, n=1;
    double temp;
    long perfect[10000];
    perfect[0]=1;
    printf("Intervaly:\n");
    input = scanf(" %d %d", &x, &y);
    while (input != EOF)
    {
        if (input == 2 && x > 0 && y > 0 && x <= y)
        {
          interval=y-x+1;
            for (long i = 2; i * i <= y; i++) { 
        long j = i * i; 
        perfect[n]=j; 
        n++;
        while (j * i <= n) { 
          perfect[n]=j*i;
            n++; 
            j = j * i; 
        } 
    }
            printf("<%d,%d> -> %d\n", x, y, interval - result);
            result=0;
        }
        else
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
        input = scanf(" %d %d", &x, &y);
    }
    return 0;
}