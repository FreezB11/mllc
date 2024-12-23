#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arr = (int*)malloc(8 * sizeof(int));    

    for (size_t i = 0; i < 8; i++)
    {
        /* code */
        arr[i] = i*i;
    }
    for (int i = 0; i < 8; i++)
    {
        /* code */
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    for (int i = 0; i < 8; i++)
    {
        /* code */
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}