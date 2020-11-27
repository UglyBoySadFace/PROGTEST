#include <stdio.h>
#include <assert.h>

void rotateArray(int array[], int arrayLen, int rotateBy)
{
    if(rotateBy>0){
    for(int i = 0; i < rotateBy; i++){    
        int j, last;    
        last = array[arrayLen-1];    
        
        for(j = arrayLen-1; j > 0; j--){    
            array[j] = array[j-1];    
        }    
        array[0] = last;    
    }    
    }else{
        for(int i = 0; i < abs(rotateBy); i++){    
        int j, first;    
        first = array[0];
        for(j = 0; j < arrayLen-1; j++){    
            array[j] = array[j+1];    
        }    
        array[arrayLen-1] = first;    
    }
    }
        
}/*
int main(void){
    int in0 []  = { 1, 2, 3, 4, 5 };
    rotateArray ( in0, 5, -2 );
    for(int loop = 0; loop < 5; loop++)
      printf("%d ", in0[loop]);
}*/