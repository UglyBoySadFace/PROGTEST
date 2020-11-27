#include <stdio.h>
#include <stdlib.h>
void quicksort(long long arr[],int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(arr[i]<=arr[pivot]&&i<last)
            i++;
         while(arr[j]>arr[pivot])
            j--;
         if(i<j){
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
         }
      }

      temp=arr[pivot];
      arr[pivot]=arr[j];
      arr[j]=temp;
      quicksort(arr,first,j-1);
      quicksort(arr,j+1,last);

   }
}
void combineElements(long long arr[], int end)
{
    int counter = 0, j_index = 1, k_index = 2;
    int temp = 0, last_j = 0, last_i = 0;
    for (int i = 0; i < end - 2; i++)
    {
        if (last_i == arr[i])
        {
            j_index++;
            k_index = i + 3;
            continue;
        }
        for (int j = j_index; j < end - 1; j++)
        {
            if (last_j == arr[j])
            {
                k_index++;
                continue;
            }
            for (int k = k_index; k < end; k++)
            {
                if ((arr[k] < arr[i] + arr[j]) && temp < arr[k])
                {
                    temp = arr[k];
                    counter++;
                }
            }
            temp = 0;
            last_j = arr[j];
            k_index++;
        }
        last_i = arr[i];
        last_j = 0;
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
    quicksort(dily,0, counter);
    long long sorted[10000];
    int sorted_counter = 0, temp = dily[0], three = 0;
    for (int i = 0; i < counter; i++)
    {
        if (dily[i] == temp && three < 3)
        {
            sorted[sorted_counter++] = dily[i];
            three++;
        }
        else if (dily[i] != temp)
        {
            sorted[sorted_counter++] = dily[i];
            temp = dily[i];
            three = 0;
        }
    }
    combineElements(sorted, sorted_counter);
    return 0;
}