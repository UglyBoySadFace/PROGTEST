#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
struct Shots
{
    int camera_ID;
    char RZ[1001];
    int mon, day, hour, min;
};
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}
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
// 0 = rovnaji se; 1 = prvni < druhy 2; = prvni > druhy
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
    char RZ[1000], mon[4], option;
    int day, hour, min, camera_ID, counter = 0, check = 0, input, monthnum, end = 0;
    struct Shots *shots;
    shots = (struct Shots *)malloc(sizeof(struct Shots *));
    printf("Data z kamer:\n");
    input = scanf(" { %d : %1000s %3s %d %d : %d %c", &camera_ID, RZ, mon, &day, &hour, &min, &option);
    while (end == 0)
    {
        if (option == '}')
            end = 1;
        if (input == 7 && (option == ',' || option == '}'))
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
            shots = (struct Shots *)realloc(shots, sizeof(struct Shots) * (counter + 1));
            shots[counter].camera_ID = camera_ID;
            strcpy(shots[counter].RZ, RZ);
            shots[counter].mon = monthnum;
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
        if (end == 0)
        {
            input = scanf(" %d : %1000s %3s %d %d : %d %c", &camera_ID, RZ, mon, &day, &hour, &min, &option);
        }
    }
    printf("Hledani:\n");
    int search, matches_counter = 0, onTime_counter = 0, before_counter = 0, after_counter = 0;
    int zleva = -1, zprava = -1;
    int *matches, *onTime, *before, *after;
    search = scanf(" %1000s %3s %d %d : %d", RZ, mon, &day, &hour, &min);
    while (search != EOF)
    {
        if (search == 5)
        {
            matches = (int *)malloc(sizeof(int));
            onTime = (int *)malloc(sizeof(int));
            before = (int *)malloc(sizeof(int));
            after = (int *)malloc(sizeof(int));
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
                    matches = (int *)realloc(matches, sizeof(int) * (matches_counter + 1));
                }
            }
            for (int i = 0; i < matches_counter; i++)
            {

                if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min, monthnum, day, hour, min) == 0)
                {
                    onTime[onTime_counter] = shots[matches[i]].camera_ID;
                    onTime_counter++;
                    onTime = (int *)realloc(onTime, sizeof(int) * (onTime_counter + 1));
                }
                else if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min, monthnum, day, hour, min) == 1)
                {

                    if (zleva == -1)
                    {
                        zleva = i;
                    }
                    else
                    {
                        if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min,
                                         shots[matches[zleva]].mon, shots[matches[zleva]].day, shots[matches[zleva]].hour, shots[matches[zleva]].min) == 2)
                        {
                            zleva = i;
                        }
                    }
                }
                else if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min, monthnum, day, hour, min) == 2)
                {

                    if (zprava == -1)
                    {
                        zprava = i;
                    }
                    else
                    {
                        if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min,
                                         shots[matches[zprava]].mon, shots[matches[zprava]].day, shots[matches[zprava]].hour, shots[matches[zprava]].min) == 1)
                        {
                            zprava = i;
                        }
                    }
                }
            }
            if (zleva != -1)
            {
                for (int i = 0; i < matches_counter; i++)
                {
                    if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min,
                                     shots[matches[zleva]].mon, shots[matches[zleva]].day, shots[matches[zleva]].hour, shots[matches[zleva]].min) == 0)
                    {
                        before[before_counter] = shots[matches[i]].camera_ID;
                        before_counter++;
                        before = (int *)realloc(before, sizeof(int) * (before_counter + 1));
                    }
                }
            }
            if (zprava != -1)
            {
                for (int i = 0; i < matches_counter; i++)
                {
                    if (compareTimes(shots[matches[i]].mon, shots[matches[i]].day, shots[matches[i]].hour, shots[matches[i]].min,
                                     shots[matches[zprava]].mon, shots[matches[zprava]].day, shots[matches[zprava]].hour, shots[matches[zprava]].min) == 0)
                    {
                        after[after_counter] = shots[matches[i]].camera_ID;
                        after_counter++;
                        after = (int *)realloc(after, sizeof(int) * (after_counter + 1));
                    }
                }
            }
            if (onTime_counter == 0 && before_counter == 0 && after_counter == 0)
            {
                printf("> Automobil nenalezen.\n");
            }
            else if (onTime_counter == 0)
            {
                if (before_counter == 0)
                {
                    printf("> Predchazejici: N/A\n");
                }
                else
                {
                    selectionSort(before, before_counter);
                    printf("> Predchazejici: %s %d %02d:%02d, %dx [", months[shots[matches[zleva]].mon], shots[matches[zleva]].day, shots[matches[zleva]].hour, shots[matches[zleva]].min, before_counter);
                    for (int i = 0; i < before_counter; i++)
                    {
                        if (i != before_counter - 1)
                        {
                            printf("%d, ", before[i]);
                        }
                        else
                        {
                            printf("%d]\n", before[i]);
                        }
                    }
                }
                if (after_counter == 0)
                {
                    printf("> Pozdejsi: N/A\n");
                }
                else
                {
                    selectionSort(after, after_counter);
                    printf("> Pozdejsi: %s %d %02d:%02d, %dx [", months[shots[matches[zprava]].mon], shots[matches[zprava]].day, shots[matches[zprava]].hour, shots[matches[zprava]].min, after_counter);
                    for (int i = 0; i < after_counter; i++)
                    {
                        if (i != after_counter - 1)
                        {
                            printf("%d, ", after[i]);
                        }
                        else
                        {
                            printf("%d]\n", after[i]);
                        }
                    }
                }
            }
            else
            {
                selectionSort(onTime, onTime_counter);
                printf("> Presne: %s %d %02d:%02d, %dx [", months[monthnum], day, hour, min, onTime_counter);
                for (int i = 0; i < onTime_counter; i++)
                {
                    if (i != onTime_counter - 1)
                    {
                        printf("%d, ", onTime[i]);
                    }
                    else
                    {
                        printf("%d]\n", onTime[i]);
                    }
                }
            }
            zleva = -1;
            zprava = -1;
            onTime_counter = 0;
            before_counter = 0;
            after_counter = 0;
            matches_counter = 0;
            free(after);
            free(before);
            free(onTime);
            free(matches);
        }
        else
        {
            free(shots);
            printf("Nespravny vstup.\n");
            return 0;
        }
        search = scanf(" %1000s %3s %d %d : %d", RZ, mon, &day, &hour, &min);
    }
}