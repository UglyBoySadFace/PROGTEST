#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void fill()
{
    int ch = getc(stdin);
}

int main(void)
{
    char fill[100][100];
    int row = 0, column = 0;
    int ch;
    //fill =(char **) malloc(sizeof(*fill));
    printf("Vypln:\n");
    while (0)
    {
        ch = getc(stdin);
        if (ch == '\n')
        {
            row++;
            column = 0;
            ch = getc(stdin);
        }
        if (ch == '\\' || ch == '/')
        {
            if (ch == EOF)
                break;

            fill[row][column] = ch;
            column++;
        }
        else
            printf("Nespravny vstup.\n");
    }
}