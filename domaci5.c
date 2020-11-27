#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Shots
{
    int camera_ID;
    char RZ[1001];
    int mon, day, hour, min;
};
int dayInMonth(int arr[], int mon, int day)
{
    if (day > arr[mon] || day < 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// 0 = rovnaji se 1 = prvni < druhy 2 = prvni > druhy
int compareTimes(int month, int day, int hour, int min, int dmonth, int dday, int dhour, int dmin)
{
    if (month == dmonth && day == dday && hour == dhour && min == dmin)
    {
        return 0;
    }

    if (month < dmonth)
    {
        return 1;
    }
    else if (month > dmonth)
    {
        return 2;
    }
    if (month == dmonth)
    {
        if (day < dday)
        {
            return 1;
        }
        else if (day > dday)
        {
            return 2;
        }
    }
    if (day == dday)
    {
        if (hour < dhour)
        {
            return 1;
        }
        else if (hour > dhour)
        {
            return 2;
        }
    }
    if (hour == dhour)
    {
        if (min < dmin)
        {
            return 1;
        }
        else if (min > dmin)
        {
            return 2;
        }
    }
    return 0;
}
int main(void)
{
    char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int days_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char RZ[1001], mon[4], option;
    int day, hour, min, camera_ID, counter = 1, check = 0, input, search, monthnum;
    struct Shots *shots;
    shots = (struct Shots *)malloc(sizeof(struct Shots *));
    printf("Data z kamer:\n");
    input = scanf(" { %d : %s %s %d %d : %d %c", &camera_ID, RZ, mon, &day, &hour, &min, &option);
    while (option != '}')
    {
        if (input == 7 && option == ',')
        {
            for (int i = 0; i < 12; i++)
            {
                if (!(strcmp(mon, months[i])))
                {
                    monthnum = i;
                    check = 1;
                    break;
                }
            }
            if (check == 0 || (dayInMonth(days_month, monthnum, day)) || hour > 23 || hour < 0 || min > 59 || min < 0)
            {
                free(shots);
                printf("Nespravny vstup.\n");
                return 0;
            }
            shots = (struct Shots *)realloc(shots, sizeof(struct Shots *) * (counter + 1));
            shots[counter].camera_ID = camera_ID;
            strcpy(shots[counter].RZ, RZ);
            shots[counter].day = day;
            shots[counter].hour = hour;
            shots[counter].min = min;
            check = 0;
            counter++;
        }
        else if (option != '}')
        {
            printf("Nespravny vstup.\n");
            free(shots);
            return 0;
        }
        input = scanf(" %d : %s %s %d %d : %d %c", &camera_ID, RZ, mon, &day, &hour, &min, &option);
    }
    printf("Hledani:\n");
    int matches_counter = 0, onTime_counter = 0, before = -1, after = -1, before_counter = 0, after_counter = 0;
    int *matches, *onTime, *before_ID, *after_ID;
    matches = (int *)malloc(sizeof(int));
    onTime = (int *)malloc(sizeof(int));
    before_ID = (int *)malloc(sizeof(int));
    after_ID = (int *)malloc(sizeof(int));
    while (search != EOF)
    {
        search = scanf(" %s %s %d %d : %d", RZ, mon, &day, &hour, &min);
        if (search == 5)
        {
            for (int i = 0; i < 12; i++)
            {
                if (!(strcmp(mon, months[i])))
                {
                    monthnum = i;
                    check = 1;
                    break;
                }
            }
            if (check == 0 || (dayInMonth(days_month, monthnum, day)) || hour > 23 || hour < 0 || min > 59 || min < 0)
            {
                free(shots);
                printf("Nespravny vstup.\n");
                return 0;
            }
            for (int i = 0; i < counter; i++)
            {
                if (!(strcmp(RZ, shots[i].RZ)))
                {
                    matches[matches_counter] = i;
                    matches_counter++;
                    matches = (int *)realloc(matches, sizeof(int) * (matches_counter+1));
                }
            }
            for (int i = 0; i < matches_counter; i++)
            {
                if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min, monthnum, day, hour, min) == 0)
                {
                    onTime[onTime_counter] = i;
                    onTime_counter++;
                    onTime = (int *)realloc(onTime, sizeof(int) * (onTime_counter+1));
                }
                else if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min, monthnum, day, hour, min) == 1)
                {

                    if (before == -1)
                    {
                        before = i;
                    }
                    else
                    {
                        if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min,
                                         shots[matches[before]].mon, shots[matches[before]].day, shots[matches[before]].hour, shots[matches[before]].min) == 2)
                        {
                            before = i;
                        }
                    }
                }
                else if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min, monthnum, day, hour, min) == 2)
                {

                    if (after == -1)
                    {
                        after = i;
                    }
                    else
                    {
                        if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min,
                                         shots[matches[after]].mon, shots[matches[after]].day, shots[matches[after]].hour, shots[matches[after]].min) == 1)
                        {
                            after = i;
                        }
                    }
                }
            }
            if (matches_counter == 0)
            {
                printf("> Automobil nenalezen.\n");
            }
            else
            {
                if (onTime_counter == 0)
                {

                    if (before == -1)
                    {
                        printf("> Predchazejici: N/A\n");
                    }
                    else
                    {
                        for (int i = 0; i < matches_counter; i++)
                        {
                            if (compareTimes(shots[matches[before]].mon, shots[matches[before]].day, shots[matches[before]].hour, shots[matches[before]].min,
                                             shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min) == 0)
                            {
                                before_ID[before_counter] = shots[matches[i]].camera_ID;
                                before_counter++;
                                before_ID = (int *)realloc(before_ID, sizeof(int) * (before_counter+1));
                            }
                        }
                        printf("> Predchazejici: %s %d %02d:%02d, %dx ", months + shots[matches[before]].mon, shots[matches[before]].day, shots[matches[before]].hour, shots[matches[before]].min, before_counter);
                        printf("[");
                        for (int i = 0; i < before_counter; i++)
                        {
                            if (i != before_counter - 1)
                            {
                                printf("%d, ", before_ID[i]);
                            }
                            else
                            {
                                printf("%d", before_ID[i]);
                            }
                        }
                        printf("]\n");
                    }
                    if (after == -1)
                    {
                        printf("> Pozdejsi: N/A\n");
                    }
                    else
                    {
                        for (int i = 0; i < matches_counter; i++)
                        {
                            if (compareTimes(shots[matches[after]].mon, shots[matches[after]].day, shots[matches[after]].hour, shots[matches[after]].min,
                                             shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min) == 0)
                            {
                                after_ID[after_counter] = shots[matches[i]].camera_ID;
                                after_counter++;
                                after_ID = (int *)realloc(after_ID, sizeof(int) * (after_counter+1));
                            }
                        }
                        printf("> Pozdejsi: %s %d %02d:%02d, %dx ", months + shots[matches[after]].mon, shots[matches[after]].day, shots[matches[after]].hour, shots[matches[after]].min, after_counter);
                        printf("[");
                        for (int i = 0; i < after_counter; i++)
                        {
                            if (i != after_counter - 1)
                            {
                                printf("%d, ", after_ID[i]);
                            }
                            else
                            {
                                printf("%d", after_ID[i]);
                            }
                        }
                        printf("]\n");
                    }
                }
                else
                {
                    printf("> Presne: %s %d %02d:%02d, %dx ", mon, day, hour, min, onTime_counter);
                    printf("[");
                    for (int i = 0; i < onTime_counter; i++)
                    {
                        if (i != onTime_counter - 1)
                        {
                            printf("%d, ", shots[matches[onTime[i]]].camera_ID);
                        }
                        else
                        {
                            printf("%d", shots[matches[onTime[i]]].camera_ID);
                        }
                    }
                    printf("]\n");
                }
                after_counter = 0;
                before_counter = 0;
                before = -1;
                after = -1;
                onTime_counter = 0;
            }
        }
        else
        {
            free(shots);
            printf("Nespravny vstup.\n");
            return 0;
        }
        matches_counter = 0;
    }
}