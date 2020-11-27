#include <stdio.h>
#include <stdlib.h>

struct triangle
{
    long long a, b, c;
    int duplicate;
};
void swap(long long *xp, long long *yp)
{
    long long temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(long long arr[], int n)
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
int isItTriangle(long long num1, long long num2, long long num3)
{
    long long max;
    if (num1 > num2)
    {
        if (num1 > num3)
        {
            max = num1;
            return (num2 + num3) > max ? 1 : 0;
        }
        else
        {
            max = num3;
            return (num1 + num2) > max ? 1 : 0;
        }
    }
    else
    {
        if (num2 > num3)
        {
            max = num2;
            return (num1 + num3) > max ? 1 : 0;
        }
        else
        {
            max = num3;
            return (num1 + num2) > max ? 1 : 0;
        }
    }
}
int removeDuplicates(long long arr[], int size)
{
    int counter = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                counter++;
            }
            else if (counter == 3 && arr[i] == arr[j])
            {
                for (int k = j; k < size; k++)
                {
                    arr[k] = arr[k + 1];
                }
                size--;
                j--;
            }
            else
            {
                counter = 1;
            }
        }
    }
    return size;
}
void combineElements(long long arr[], int end)
{
    struct triangle tri[100000];
    int counter = 0, j_index = 1, k_index = 2, duplicate = 0;
    for (int i = 0; i < end - 2; i++)
    {
        for (int j = j_index; j < end - 1; j++)
        {
            for (int k = k_index; k < end; k++)
            {
                if (isItTriangle(arr[i], arr[j], arr[k]))
                {
                    if (counter == 0)
                    {
                        printf("%lld %lld %lld \n", arr[i], arr[j], arr[k]);
                        tri[counter].a = arr[i];
                        tri[counter].b = arr[j];
                        tri[counter].c = arr[k];
                        counter++;
                    }
                    else
                    {
                        for (int l = 0; l < counter; l++)
                        {
                            if (arr[i] == tri[l].a && arr[j] == tri[l].b && arr[k] == tri[l].c)
                            {
                                duplicate = 1;
                                break;
                            }
                        }
                        if (duplicate == 0)
                        {
                            printf("%lld %lld %lld \n", arr[i], arr[j], arr[k]);
                            tri[counter].a = arr[i];
                            tri[counter].b = arr[j];
                            tri[counter].c = arr[k];
                            counter++;
                        }else{
                            duplicate=0;
                        }
                    }
                }
            }
            k_index++;
        }
        j_index++;
        k_index = i + 3;
    }
    printf("Trojuhelniku: %d\n", counter);
}

int main(void)
{
    int input, counter = 0;
    long long dil;
    long long dily[10000];
    printf("Delky nosniku:\n");
    input = scanf("%lld", &dil);
    if (input != 1 || dil < 1)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    while (input != EOF)
    {
        dily[counter] = dil;
        counter++;
        input = scanf("%lld", &dil);
        if ((input != 1 && input != EOF) || dil < 1)
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    if (counter < 3)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    selectionSort(dily, counter);
    counter = removeDuplicates(dily, counter);
    combineElements(dily, counter);
    return 0;
}