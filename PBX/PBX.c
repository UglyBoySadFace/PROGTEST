#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

struct User
{
    char *phone, *username;
};
void formatInput(char *input)
{
    char *d = input;
    int space = 2;
    if ((*d == '+' || *d == '-' || *d == '?'))
    {
        while (*input)
        {
            if (space)
            {
                if (!isblank(*input))
                {
                    space = 0;
                    *d++ = *input++;
                }
                else
                    input++;
            }
            else
            {
                if (isblank(*input))
                    space = 1;
                *d++ = *input++;
            }
        }
        if (space == 1)
            d--;
        *d = '\0';
    }
    else
    {
        *input = 0;
        return;
    }
}
//false -> N/All DIGITS
int checkDigits(char *number)
{
    while (*number)
    {
        if (!(isdigit(*number++)))
            return 0;
    }
    return 1;
}
int checkName(char *name)
{
    int pass = 0;
    while (*name)
    {
        if (*name == '"' && !pass)
        {
            pass++;
        }
        else if (*name == '"')
        {
            pass++;
        }
        name++;
    }
    if (pass == 2)
        return 1;
    else
        return 0;
}
void removeChar(char *str, char garbage)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst != garbage)
            dst++;
    }
    *dst = '\0';
}
int main(void)
{
    printf("PBX configuration (+ = set, - = delete, ? = test, EOF = quit):\n");
    struct User *record;
    record = (struct User *)malloc(sizeof(struct User));
    size_t capacity = 0;
    int counter = 0, fail = 0, record_counter = 0;
    char option, *input, *name, *number;
    while (getline(&input, &capacity, stdin) != -1)
    {
        formatInput(input);
        if (*input == 0 && !fail)
        {
            printf("INVALID COMMAND\n");
            fail = 1;
        }
        if (!fail)
        {
            char *info = strtok(input, " ");
            while (info != NULL)
            {
                if (counter == 0)
                    option = *info;
                if (counter == 1)
                    number = info;
                if (counter == 2)
                    name = info;
                info = strtok(NULL, " ");
                counter++;
            }
            switch (option)
            {
            case '+':
                if ((!checkDigits(number) || !checkName(name) || counter != 3))
                {
                    printf("INVALID COMMAND\n");
                    fail = 1;
                }
                else
                {
                    removeChar(name, '"');
                    
                    printf("option => %c number => %s name=> %s \n", option, number, name);
                }
                break;
            case '?':
                if (!checkDigits(number) || counter != 2)
                {
                    printf("INVALID COMMAND\n");
                    fail = 1;
                }
                else
                {
                }
                break;
            case '-':
                if (!checkDigits(number) || counter != 2)
                {
                    printf("INVALID COMMAND\n");
                    fail = 1;
                }
                else
                {
                }
                break;
            default:
                break;
            }
        }
        fail = 0;
        counter = 0;
    }
}