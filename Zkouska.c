#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compareInt(const void *pa, const void *pb)
{
    return (*(int *)pa - *(int *)pb);
}

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#endif /* __PROGTEST__ */

struct Domino
{

    int number1;
    int number2;

    int number3;
    int number4;

    char *name;
};

int countCollectible(const char *list)
{
    int startRead = 0, size = 0, count = 0;
    char *name = NULL, *rest = NULL;
    const char *temp = list;
    name = (char *)malloc(sizeof(char));
    struct Domino *domino;
    domino = (struct Domino *)malloc(sizeof(struct Domino));
    while (*list)
    {
        if (*list == '\'' && startRead == 0)
        {
            list++;
            startRead = 1;
        }
        else if (*list == '\'' && startRead)
        {
            list++;
            startRead = 0;
            domino = (struct Domino *)realloc(domino, sizeof(struct Domino) * (count + 1));
            (domino + count)->name = (char *)malloc(sizeof(char) * size);
            strcpy((domino + count)->name, name);
            count++;
            free(name);
            name = (char *)malloc(sizeof(char));
            size = 0;
        }
        if (startRead)
        {
            name = (char *)realloc(name, sizeof(char) * (size + 1));
            name[size] = *list;
            size++;
        }
        list++;
    }
    char *num;
    num = (char *)malloc(sizeof(char));
    int num_count = 0;
    int side_count = 0;
    int load = 0;
    while (*temp)
    {
        if (*temp == '[')
        {
            startRead = 1;
            //strtol();
        }
        if (startRead)
        {
            if (isdigit(*temp))
            {
                num = (char *)realloc(num, sizeof(char) * (num_count + 1));
                num[num_count++] = *temp;
            }
            if (*temp == '|')
            {
                if (side_count % 4 == 0)
                {
                    domino[load].number1 = atoi(num);
                }
                else if (side_count % 4 == 2)
                {
                    domino[load].number3 = atoi(num);
                }
                side_count++;
                free(num);
                num = (char *)malloc(sizeof(char));
                num_count = 0;
            }
            if (*temp == ']')
            {
                if (side_count % 4 == 1)
                {
                    domino[load].number2 = atoi(num);
                }
                else if (side_count % 4 == 3)
                {
                    domino[load].number4 = atoi(num);
                }
                side_count++;
                if (side_count % 4 == 0)
                    load++;
                free(num);
                num = (char *)malloc(sizeof(char));
                num_count = 0;
                startRead = 0;
            }
        }
        temp++;
    }
    int result = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp((domino + i)->name, "Segfault Extreme") == 0 && ((domino[i].number1 + domino[i].number2) == 48 ||
                                                                    (domino[i].number3 + domino[i].number4) == 48))
        {
            if (!(domino[i].number1 + domino[i].number2 == 48 && domino[i].number3 + domino[i].number4 == 48))
                result++;
        }
    }
    return result;
}

int countUnique(const char *list)
{
    return 0; /* TODO */
}

uint64_t countTowers(const char *list)
{
    return 0; /* TODO */
}

#ifndef __PROGTEST__
int main(void)
{
    //qsort(a, i, sizeof(int), compareInt);
    const char *str1 =
        " { 'Progtest Exam' ; [ 12 | 23 ] ; [ 35 | 4 ] }{'PA1 2020/2021';[2|2];[3|1]}\n"
        "{'Progtest Exam' ; [ 2 | 1 ] ; [ 3 | 4 ] }\n"
        "{'Progtest Exam' ; [ 2 | 3 ] ; [ 1 | 4 ] }\n";
    const char *str2 =
        "{'Crash';  [1|2];[3|4]}\n"
        "{'MemLeak';[1|2];[3|4]}\n"
        "{'MemLeak';[2|3];[3|1]}\n"
        "{'MemLeak';[1|3];[3|2]}\n"
        "{'MemLeak';[1|4];[1|5]}\n"
        "{'MemLeak';[4|1];[1|5]}\n"
        "{'MemLeak';[4|1];[5|1]}\n"
        "{'MemLeak';[1|4];[5|1]}\n"
        "{'MemLeak';[1|5];[1|4]}\n"
        "{'MemLeak';[5|1];[1|4]}\n"
        "{'MemLeak';[5|1];[4|1]}\n"
        "{'MemLeak';[1|5];[4|1]}\n";
    const char *str3 =
        "{'-Wall -pedantic -Werror -Wno-long-long -O2';[2|2];[3|3]}\n"
        "{'-Wall -pedantic -Werror -Wno-long-long -O2';[4|4];[5|5]}\n"
        "{'-Wall -pedantic -Werror -Wno-long-long -O2';[3|4];[4|5]}\n";
    const char *str4 =
        "{'-fsanitize=address -g';[1|5];[5|7]}\n"
        "{'-fsanitize=address -g';[3|7];[1|9]}\n"
        "{'-fsanitize=address -g';[2|2];[4|7]}\n"
        "{'-fsanitize=address -g';[3|9];[2|6]}\n"
        "{'-fsanitize=address -g';[2|2];[2|2]}\n";

    assert(countCollectible(str1) == 0);
    assert(countUnique(str1) == 3);
    assert(countUnique(str2) == 4);
    assert(countUnique(str3) == 3);
    assert(countUnique(str4) == 5);
    assert(countTowers(str3) == 10);
    assert(countTowers(str4) == 114);
    return 0;
}
#endif /* __PROGTEST__ */
