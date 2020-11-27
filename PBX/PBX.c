#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

struct Record
{
    int active;
    char *number, *name;
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
        {
            printf(" not a dig > %c \n", *number);
            return 0;
        }
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
void stripLF(char *line)
{
    int l = strlen(line);
    if (l > 0 && line[l - 1] == '\n')
        line[l - 1] = 0;
}
int T9(char *name, char *number)
{
    char buttons[9][5] = {
        {'1', ' ', '\0'},
        {'2', 'a','b','c', '\0'},
        {'3', ' ', '\0'},
        {'4', ' ', '\0'},
        {'5', ' ', '\0'},
        {'6', ' ', '\0'},
        {'7', ' ', '\0'},
        {'8', ' ', '\0'},
        {'9', ' ', '\0'},
    };
}
int main(void)
{
    printf("PBX configuration (+ = set, - = delete, ? = test, EOF = quit):\n");
    struct Record *record;
    record = (struct Record *)malloc(sizeof(struct Record));
    size_t capacity = 0, record_size;
    int counter = 0, fail = 0, record_counter = 0, update = 0, matches = 0, deleted = 0;
    char option, *input, *name, *number, *matched_name;
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
                    stripLF(name);
                    removeChar(name, '"');
                    if (record_counter == 0)
                    {
                        record[record_counter].name = strdup(name);
                        record[record_counter].number = strdup(number);
                        record[record_counter].active = 1;
                        printf("NEW\n");
                        record_counter++;
                        record = (struct Record *)realloc(record, sizeof(struct Record) * pow(2, record_counter + 1));
                    }
                    else
                    {
                        for (int i = 0; i < record_counter; i++)
                        {
                            if (!strcmp(record[i].number, number))
                            {
                                if (record[i].active == 0)
                                {
                                    record[i].name = strdup(name);
                                    record[i].active = 1;
                                    printf("NEW\n");
                                    update = 1;
                                    break;
                                }
                                else
                                {
                                    record[i].name = strdup(name);
                                    update = 1;
                                    printf("UPDATE\n");
                                    break;
                                }
                            }
                        }
                        if (update)
                        {
                            update = 0;
                        }
                        else
                        {
                            record[record_counter].name = strdup(name);
                            record[record_counter].number = strdup(number);
                            record[record_counter].active = 1;
                            printf("NEW\n");
                            record_counter++;
                            record = (struct Record *)realloc(record, sizeof(struct Record) * pow(2, record_counter + 1));
                        }
                    }
                    for (int i = 0; i < record_counter; i++)
                        printf("#%s name:%s active:%d\n", record[i].number, record[i].name, record[i].active);
                }
                break;
            case '?':
                stripLF(number);
                if (!checkDigits(number) || counter != 2)
                {
                    printf("INVALID COMMAND\n");
                    fail = 1;
                }
                else
                {
                    for (int i = 0; i < record_counter; i++)
                    {
                        if (!strcmp(record[i].number, number) && record[i].active == 1)
                        {
                            matches++;
                            matched_name = record[i].name;
                            break;
                        }
                    }
                    if (!matches)
                        printf("NOT FOUND\n");
                    if (matches == 1)
                    {
                        printf("FOUND %s (%s)\n", number, matched_name);
                        matches = 0;
                    }
                    else
                    {
                        printf("FOUND AMBIGUOUS %d\n", matches);
                    }
                }
                break;
            case '-':
                stripLF(number);
                if (!checkDigits(number) || counter != 2)
                {
                    printf("INVALID COMMAND\n");
                    fail = 1;
                }
                else
                {
                    for (int i = 0; i < record_counter; i++)
                    {
                        if (!strcmp(record[i].number, number) && record[i].active == 1)
                        {
                            record[i].active = 0;
                            deleted = 1;
                            printf("DELETED\n");
                            break;
                        }
                    }
                    if (deleted)
                    {
                        deleted = 0;
                    }
                    else
                    {
                        printf("NOT FOUND\n");
                    }
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