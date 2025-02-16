#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


enum SORTING_METHOD_TYPE
{
    BUBBLE_SORTING = 0,
    MERGE_SORTING,
    INSERTION_SORTING,
    SELECTION_SORTING,
    QUICK_SORTING,
    SORTING_METHOD_MAX,
};
// ===========================================================================
// Common Utilites
// ===========================================================================
void Swap(int * a, int * b)
{
    int swap  = *a;
    *a  = *b;
    *b = swap;     
}


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
                Swap( &dataArry[idx2],&dataArry[idx2+1]);      
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

// ===========================================================================
// Insertion Sorting
// ===========================================================================
void InsertionSorting(int * dataArry, int dataMax)
{
    if(NULL == dataArry)
        return;

    int currentVal, l1, l2 ;
    int isValueChanged = 0;
    for(l1 = 1 ; l1 < dataMax-1; l1++)
    {
        currentVal = dataArry[l1];
        isValueChanged = 0;
        for(l2 = l1-1; l2 >= 0; l2--)
        {
            // If this l2 value is less than or equal to current value, it is a right place for it
            if(dataArry[l2] <= currentVal)
                break;
            
            // If this l2 is greater than current value, shift it to its next place
            dataArry[l2+1] = dataArry[l2];
            isValueChanged = 1;
        }

        // If value is changed at least one, need to place current value to the last position of l2
        if(isValueChanged)
        {
             dataArry[l2+1] = currentVal;
        }
    }
}

// ===========================================================================
// Selection Sorting
// ===========================================================================
void SelectionSorting(int * dataArry, int dataMax)
{
    if(NULL == dataArry)
        return;

    for(int i = 0 ; i < dataMax; i++)
    {
        // Find minimum value than this selected value
        int selectedPos = i;

        // Search start from the current position + 1
        for( int j = i+1; j < dataMax; j++)
        {
            // If find value is less than, store that position
            if(dataArry[selectedPos] > dataArry[j])
            {
                selectedPos = j;
            }
        }

        // Swap the value if position is different than current position
        if(i != selectedPos)
        {
            Swap(&dataArry[i],&dataArry[selectedPos]);
        }
    } 
}



// ===========================================================================
// Quick Sorting
// ===========================================================================
int Parition(int * dataArray, int low, int high)
{
    int pivot = dataArray[high];
    int i = low-1;
    
    // i is used to set partition where 
    // all left side elements should be smaller than pivot number
    // all right side elements should be greater than pivot number
    for(int j = low; j < high; j++)
    {
        if(dataArray[j] <= pivot)
        {
            i++;
            Swap(&dataArray[i],&dataArray[j]);
        }
    }

    // set pivot number at ith position and then return i value as a center of parition
    Swap(&dataArray[i+1],&dataArray[high]);
    return i+1;
}

void QuickSort(int * dataArray, int low, int high)
{
    if(low < high)
    {
        int p = Parition(dataArray, low, high);

        QuickSort(dataArray, low, p-1);
        QuickSort(dataArray, p+1, high);
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
        case INSERTION_SORTING:
            InsertionSorting(dataArray,dataMax);
            strcpy(methodName,"Insertion Sorting");
            break;
        case SELECTION_SORTING:
            SelectionSorting(dataArray,dataMax);
            strcpy(methodName,"Selection Sorting");
            break;
        case QUICK_SORTING:
            QuickSort(dataArray,0,dataMax-1);
            strcpy(methodName,"Quick Sorting");
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
