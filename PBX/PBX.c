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
int formatName(char *input)
{
    char *d = input;
    if (*input == '"')
        input++;
    else
        return 0;
    while (*input)
    {
        if (*input == '"' && *++input == 0)
        {
            *d = 0;
            return 1;
        }
        else
            *d++ = *input++;
    }
    return 0;
}
void formatInput(char *input)
{
    char *d = input;
    int space = 2;
    if (*input == ' ')
    {
        *input = 0;
    }
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
//false -> N/All DIGITS
int checkDigits(char *number)
{
    while (*number)
    {
        if (!(isdigit(*number++)))
        {
            return 0;
        }
    }
    return 1;
}
void stripLF(char *line)
{
    long int l = strlen(line);
    if (l > 0 && line[l - 1] == '\n')
        line[l - 1] = 0;
}
int T9(char *name, char *number)
{
    char buttons[9][6] = {
        {'1', ' ', '\0'},
        {'2', 'a', 'b', 'c', '\0'},
        {'3', 'd', 'e', 'f', '\0'},
        {'4', 'g', 'h', 'i', '\0'},
        {'5', 'j', 'k', 'l', '\0'},
        {'6', 'm', 'n', 'o', '\0'},
        {'7', 'p', 'q', 'r', 's', '\0'},
        {'8', 't', 'u', 'v', '\0'},
        {'9', 'w', 'x', 'y', 'z', '\0'}};
    char n0[36] = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
        'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
    long int num_len = strlen(number),
             name_len = strlen(number);
    int char_to_num,
        temp = 0;
    if (num_len == name_len)
    {
        for (long int i = 0; i < num_len; i++)
        {
            char_to_num = *number - '0';
            for (long int j = 0; j < 37; j++)
            {
                if (char_to_num == 0)
                {
                    if (n0[j] == tolower(*name))
                    {
                        temp = 0;
                        break;
                    }
                    else
                        temp = 1;
                }
                else
                {
                    if (buttons[char_to_num - 1][j] == '\0')
                    {
                        temp = 0;
                        break;
                    }
                    if (buttons[char_to_num - 1][j] == tolower(*name))
                    {
                        temp = 1;
                        break;
                    }
                }
            }
            if (!temp)
                return 0;
            number++;
            name++;
        }
        return 1;
    }
    else
        return 0;
}
int main(void)
{
    printf("PBX configuration (+ = set, - = delete, ? = test, EOF = quit):\n");
    struct Record *record;
    record = (struct Record *)malloc(sizeof(struct Record));
    size_t capacity = 0, record_size = 0;
    int counter = 0, fail = 0, record_counter = 0, update = 0, matches = 0, deleted = 0;
    long int skip;
    char hah[] = "lol";
    char option = 'q', *input = hah, *temp_input = hah, *name = hah, *number = hah, *matched_name = hah, *matched_number = hah, *info = hah;
    while (getline(&input, &capacity, stdin) != -1)
    {
        formatInput(input);
        stripLF(input);
        if (!(*input == '+' || *input == '-' || *input == '?') || *input == 0 || input[1] == 0)
        {
            printf("INVALID COMMAND\n");
            fail = 1;
        }
        else
        {
            temp_input = strdup(input);
            info = strtok(input, " ");
            while (info != NULL)
            {
                if (counter == 0)
                    option = *info;
                if (counter == 1)
                    number = info;
                if (counter == 2)
                    break;
                info = strtok(NULL, " ");
                counter++;
            }
            if (option == '+')
            {
                skip = strlen(number) + 3;
                for (int i = 0; i < skip; i++)
                    memmove(&temp_input[0], &temp_input[1], strlen(temp_input));
            }
            if (number == NULL && !fail)
            {
                counter = 0;
                printf("INVALID COMMAND\n");
                continue;
            }
        }
        if (!fail)
        {
            switch (option)
            {
            case '+':
                if ((!checkDigits(number) || counter != 2))
                {
                    printf("INVALID COMMAND\n");
                    break;
                }
                else if (formatName(temp_input))
                {
                    name = temp_input;
                    if (record_counter == 0)
                    {
                        record[record_counter].name = strdup(name);
                        record[record_counter].number = strdup(number);
                        record[record_counter].active = 1;
                        printf("NEW\n");
                        record_counter++;
                        record_size = sizeof(struct Record) * pow(2, record_counter);
                        record = (struct Record *)realloc(record, record_size);
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
                                    printf("UPDATED\n");
                                    break;
                                }
                            }
                        }
                        if (update)
                            update = 0;
                        else
                        {
                            record[record_counter].name = strdup(name);
                            record[record_counter].number = strdup(number);
                            record[record_counter].active = 1;
                            printf("NEW\n");
                            record_counter++;
                            record_size = sizeof(struct Record) * (record_counter + 1);
                            record = (struct Record *)realloc(record, record_size);
                        }
                    }
                }
                else
                {
                    printf("INVALID COMMAND\n");
                    break;
                }
                break;
            case '?':
                if (!checkDigits(number) || counter != 2)
                {
                    printf("INVALID COMMAND\n");
                    break;
                    ;
                }
                else
                {
                    for (int i = 0; i < record_counter; i++)
                    {
                        if (T9(record[i].name, number) && record[i].active == 1)
                        {
                            matches++;
                            matched_number = record[i].number;
                            matched_name = record[i].name;
                        }
                    }
                    for (int i = 0; i < record_counter; i++)
                    {
                        if (!strcmp(record[i].number, number) && record[i].active == 1)
                        {
                            if (!(!strcmp(record[i].number, matched_number) && (!strcmp(record[i].name, matched_name))))
                            {
                                matches++;
                                matched_number = record[i].number;
                                matched_name = record[i].name;
                            }
                        }
                    }
                    if (!matches)
                        printf("NOT FOUND\n");
                    if (matches == 1)
                    {
                        printf("FOUND %s (%s)\n", matched_number, matched_name);
                        matched_number = hah;
                        matched_name = hah;
                        matches = 0;
                    }
                    else if (matches > 1)
                    {
                        printf("AMBIGUOUS (%d matches)\n", matches);
                    }
                }
                break;
            case '-':
                if (!checkDigits(number) || counter != 2)
                {
                    printf("INVALID COMMAND\n");
                    continue;
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
                        deleted = 0;
                    else
                        printf("NOT FOUND\n");
                }
                break;
            default:
                printf("INVALID COMMAND\n");
                break;
            }
        }
        matches = 0;
        fail = 0;
        counter = 0;
    }
    free(record);
    free(input);
    free(temp_input);
}