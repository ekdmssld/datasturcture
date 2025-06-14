#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int list[MAX];
int n;

void selection_sort(int list[], int n){
    int i, j, least, temp;
    for(i = 0; i < n-1; i++){
        least = i;
        for(j = i+1; j < n; j++)
            if(list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], temp);
    }
}

void insertion_sort(int list[], int n){
    int i, j, key;
    for(i=1; i<n; i++){
        key = list[i];
        for(j = i-1;j >= 0 && list[j]>key; j--)
            list[j+1] = list[j];
        list[j+1] = key;
    }
}

void bubble_sort(int list[], int n){
    int i, j, temp;
    for(i = n-1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(list[j] > list[j+1])
                SWAP(list[j], list[j+1], temp);
        }
    }
}

void inc_insert_sort(int list[], int first, int last, int gap){
    int i, j, key;
    for(i = first+gap; i <= last; i += gap){
        key = list[i];
        for(j = i-gap; j >= first && list[j] > key; j -= gap)
            list[j+gap] = list[j];
        list[j+gap] = key;
    }
}

void shell_sort(int list[], int n){
    int gap, i;
    for(gap = n/2; gap > 0; gap /= 2){
        for(i = 0; i < gap; i++)
            inc_insert_sort(list, i, n-1, gap);
    }
}
int sorted[MAX];
void merge(int list[], int left, int mid, int right){
    int i, j, k, l;
    i = left; j = mid + 1; k = left;
    while(i <= mid && j <= right){
        if(list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if(i > mid){
        for(l = j; l <= right; l++)
            sorted[k++] = list[l];
    }
    else{
        for(l = i; l <= mid; l++)
            sorted[k++] = list[l];
    }
    for(l = left; l <= right; l++)
        list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right){
    int mid;
    if (left < right){
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}
void quick_sort(int list[], int left, int right){
    if(left < right){
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}
int partition(int list[], int left, int right){
    int pivot, temp;
    int low, high;
    
    low = left;
    high = right + 1;
    pivot = list[left];
    do{
        do{
            low++;
        }while(list[low] < pivot);
        do{
            high--;
    }while(list[high] > pivot);
    if(low < high){
        SWAP(list[low], list[high], temp);
    }
}while(low < high);
    SWAP(list[left], list[high], temp);
    return high;
}
int main(){
    int i;
    n = MAX;
    srand(time(NULL));

    for(i = 0; i < n; i++)
        list[i] = rand() % 100;
    selection_sort(list, n);
    for(i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    return 0;
}