#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


enum SORTING_METHOD_TYPE
{
    BUBBLE_SORTING = 0,
    MERGE_SORTING,
    SORTING_METHOD_MAX,


};

// ===========================================================================
// Bubble Sorting
// ===========================================================================
void BubbleSort(int * dataArry, int dataMax)
{
    if(NULL == dataArry)
        return;


    int swap = 0;

    for (int idx1 = 0 ; idx1 <= dataMax - 1; idx1++)
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


// ===========================================================================
// Merge Sorting
// ===========================================================================
void Merging(int * dataArry, int leftIdx, int MidIndx, int rightIdx)
{
    // Derive Maximum possible elements from left and right index
    // i.e left = 20, mid = 25, right = 30... Maximum Element = 30-20 = 10 elements
    int tMaxElement = rightIdx-leftIdx+1;
    int * tempArray = (int *) malloc(sizeof(int) * tMaxElement);

    // Don't proceed if malloc is failed to allocate memory
    if(tempArray == NULL)
        return;

    // use two variable to point two different indices
    int l1 = leftIdx;
    int l2 = MidIndx+1;

    // store sorted data into temp array
    for(int i =0; i < tMaxElement; i++)
    {
        // Lowest element into temp array from either left or right 
        if(l1 <= MidIndx && l2 <= rightIdx)
        {
            if(dataArry[l1] < dataArry[l2])
                tempArray[i] = dataArry[l1++];
            else
                tempArray[i] = dataArry[l2++];
        }

        // Transfer element into temp array if left index are not reached to its limit
        else if(l1 <= MidIndx)
        {
            tempArray[i] = dataArry[l1++];
        }
        else if(l2 <= rightIdx)
        {
            tempArray[i] = dataArry[l2++];
        }
    }

    // Move sorted data into original array
    for(int i =0; i < tMaxElement; i++)
    {
        dataArry[leftIdx+i] = tempArray[i];
    }
}


void MergeSort(int * dataArry, int leftIdx, int rightIdx)
{
    if(leftIdx < rightIdx)
    {
        int mid = leftIdx + (rightIdx - leftIdx) / 2;
        MergeSort(dataArry,leftIdx,mid);
        MergeSort(dataArry,mid+1,rightIdx);

        Merging(dataArry, leftIdx, mid, rightIdx);
    }

}

void UseSortingMethod(int Method, int * dataArray, int dataMax)
{
    // Record start time
    clock_t start = clock();

    char methodName[20];

    switch(Method)
    {
        case BUBBLE_SORTING:
            BubbleSort(dataArray,dataMax);
            strcpy(methodName,"Bubble Sorting");
            break;;
        case MERGE_SORTING:
            MergeSort(dataArray,0,dataMax-1);
            strcpy(methodName,"Merge Sorting");
            break;
        default:
            return;
    }

    // Record end time
    clock_t end = clock();

    // Calculate time taken in seconds
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nMethod Type=%s: \n", methodName);
    for(int i = 0; i < dataMax; i++)
    {
        printf("%d-",dataArray[i]);
    }

    printf("\nTime taken for sorting %d data in %f seconds\n", dataMax, timeTaken);

}

int main(void)
{
    // Test data: Unsorted array
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int orgArr[n];


    for(int MethodType = BUBBLE_SORTING; MethodType < SORTING_METHOD_MAX;MethodType++)
    {
        memcpy(orgArr,arr,sizeof(arr));
        UseSortingMethod(MethodType, orgArr,n);
    }


}