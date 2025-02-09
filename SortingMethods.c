#include <stdio.h>
#include <time.h>


enum SORTING_METHOD_TYPE
{
    BUBBLE_SORTING = 0,
    SORTING_METHOD_MAX,


};

void BubbleSort(int * dataArry, int dataMax)
{
    if(dataArry)
        return;


    int swap = 0;

    for (int idx1 = 0 ; idx1 < dataMax - 1; idx1++)
    {
         for (int idx2 = 0 ; idx2 < dataMax - idx1 - 1; idx2++)
        {
            if (dataArry[idx2] > dataArry[idx2+1]) /* For decreasing order use < */
            {
                swap  = dataArry[idx2];
                dataArry[idx2]   = dataArry[idx2+1];
                dataArry[idx2+1] = swap;       
            }
        }
    }
}


void UseSortingMethod(int Method, int * dataArray, int dataMax)
{
    switch(Method)
    {
        case BUBBLE_SORTING:
            BubbleSort(dataArray,dataMax);
            return;
        default:
            return;
    }

}

int main(void)
{
    // Test data: Unsorted array
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);


    for(int MethodType = BUBBLE_SORTING; MethodType < SORTING_METHOD_MAX;MethodType++)
    {
        // Record start time
        clock_t start = clock();

        UseSortingMethod(MethodType, arr,n);

        // Record end time
        clock_t end = clock();

        // Calculate time taken in seconds
        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\nTime taken for sorting %d data in %f seconds\n", n, timeTaken);
    }


}