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
    int num_len = strlen(number),
        name_len = strlen(number),
        char_to_num, temp = 0;
    if (num_len == name_len)
    {
        for (int i = 0; i < num_len; i++)
        {
            char_to_num = *number - '0';
            for (int j = 0; j < 37; j++)
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
    int temp_counter = 0, counter = 0, fail = 0, record_counter = 0, update = 0, matches = 0, deleted = 0;
    char hah[] = "lol";
    char option = 'q', *input, *name = NULL, *number = NULL, *matched_name = hah, *matched_number = hah, *temp_info, *info;
    while (getline(&input, &capacity, stdin) != -1)
    {
        formatInput(input);
        if (!(*input == '+' || *input == '-' || *input == '?') || *input == 0)
        {
            printf("INVALID COMMAND\n");
            fail = 1;
        }
        info = strtok(input, " ");
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
        if (name != NULL)
        {
            stripLF(name);
            temp_info = strtok(name, "\"");
            while (temp_info != NULL)
            {
                if (temp_counter == 0)
                    name = temp_info;
                temp_info = strtok(NULL, "\"");
                temp_counter++;
            }
        }
        if (number == NULL)
        {
            temp_counter = 0;
            counter = 0;
            printf("INVALID COMMAND\n");
            continue;
        }
        if (!fail)
        {
            switch (option)
            {
            case '+':
                if ((!checkDigits(number) || counter != 3 || temp_counter > 1))
                {
                    printf("INVALID COMMAND\n");
                    break;
                }
                else
                {
                    if (record_counter == 0)
                    {
                        record[record_counter].name = strdup(name);
                        record[record_counter].number = strdup(number);
                        record[record_counter].active = 1;
                        printf("NEW\n");
                        record_counter++;
                        record_size = sizeof(struct Record) * pow(2, record_counter + 1);
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
                            record_size = sizeof(struct Record) * pow(2, record_counter + 1);
                            record = (struct Record *)realloc(record, record_size);
                        }
                    }
                }
                break;
            case '?':
                stripLF(number);
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
                stripLF(number);
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
        temp_counter = 0;
    }
    free(record);
}