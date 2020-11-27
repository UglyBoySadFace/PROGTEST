#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

struct Record
{
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
struct Record *remove_element(struct Record *array, int sizeOfArray, int indexToRemove)
{
    struct Record *temp = (struct Record *)malloc((sizeOfArray - 1) * sizeof(struct Record)); // allocate an array with a size 1 less than the current one

    if (indexToRemove != 0)
        memcpy(temp, array, indexToRemove * sizeof(struct Record)); // copy everything BEFORE the index

    if (indexToRemove != (sizeOfArray - 1))
        memcpy(temp + indexToRemove, array + indexToRemove + 1, (sizeOfArray - indexToRemove - 1) * sizeof(struct Record)); // copy everything AFTER the index

    free(array);
    return temp;
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
                    removeChar(name, '"');
                    if (record_counter == 0)
                    {
                        record[record_counter].name = strdup(name);
                        record[record_counter].number = strdup(number);
                        //strcpy(record[record_counter].name, name);
                        //strcpy(record[record_counter].number, number);
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
                                record[i].name = strdup(name);
                                //strcpy(record[i].name, name);
                                update = 1;
                                printf("UPDATE\n");
                                break;
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
                            //strcpy(record[record_counter].name, name);
                            //strcpy(record[record_counter].number, number);
                            printf("NEW\n");
                            record_counter++;
                            record = (struct Record *)realloc(record, sizeof(struct Record) * pow(2, record_counter + 1));
                        }
                    }
                    for (int i = 0; i < record_counter; i++)
                        printf("#%s:%s\n", record[i].number, record[i].name);
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
                    for (int i = 0; i < record_counter; i++)
                    {
                        if (!strcmp(record[i].name, name))
                        {
                            matches++;
                            matched_name = name;
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
                    for (int i = 0; i < record_counter; i++)
                    {
                        if (!strcmp(record[i].number, number))
                        {
                            remove_element(record, record_counter, i);
                            deleted = 1;
                            printf("DELETED\n");
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