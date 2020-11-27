#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
char *getname()
{
    char *line = NULL, *tmp = NULL;
    size_t size = 0, index = 0, fuck = 1;
    int ch = EOF;
    while (ch)
    {
        ch = getc(stdin);
        if (ch == '\t')
        {
            fuck = 0;
        }
        if (fuck)
        {
            if (ch == EOF)
            {
                if (index > 0)
                {
                    line[0] = 0;
                    return line;
                }
                return NULL;
            }
            if (ch == '\n')
                ch = 0;

            if (isspace(ch))
            {
                continue;
            }
            if (size <= index)
            {
                size += sizeof(char);
                tmp = (char *)realloc(line, size);
                if (!tmp)
                {
                    free(line);
                    line = NULL;
                    break;
                }
                line = tmp;
            }
            line[index++] = ch;
        }
        else
        {
            if (ch == EOF)
            {
                if (size <= index)
            {
                size += sizeof(char);
                tmp = (char *)realloc(line, size);
                if (!tmp)
                {
                    free(line);
                    line = NULL;
                    break;
                }
                line = tmp;
            }
            line[index++] = 0;
                return line;
            }
        }
    }
    return line;
}
void ispalindrom(char *string)
{
    int sensitive = 1;
    int insensitive = 1;
    int count = strlen(string);
    for (int i = 0; i < count / 2; i++)
    {
        if (!(string[i] == string[count - 1 - i]))
        {
            insensitive = 0;
            break;
        }
    }
    if (insensitive)
    {
        printf("Retezec je palindrom (case-sensitive).\n");
        free(string);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        string[i] = tolower(string[i]);
    }
    for (int i = 0; i < count / 2; i++)
    {
        if (!(string[i] == string[count - 1 - i]))
        {
            sensitive = 0;
            break;
        }
    }
    if (sensitive)
    {
        printf("Retezec je palindrom (case-insensitive).\n");
        free(string);
        return;
    }
    printf("Retezec neni palindrom.\n");
    free(string);
}
int main(void)
{
    char *string;
    printf("Zadejte retezec:\n");
    while (1)
    {
        string = getname();
        if (string == NULL)
        {
            break;
        }
        if (string[0] == '\0')
        {
            free(string);
            printf("Nespravny vstup.\n");
        }
        else
            ispalindrom(string);
    }
}
