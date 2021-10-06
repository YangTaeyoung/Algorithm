#include <iostream>
using namespace std;

const int number = 8;
int sorted[8]; // 정렬배열은 공간낭비를 막기 위해 항상 전역변수로 선언.

int merge(int arr[], int m, int mid, int n) {
    int i = m;
    int j = mid + 1;
    int k = m;
    // 작은 순서대로 배열에 삽입
    while (i <= mid && j <= n) {
        if (arr[i] <= arr[j]) {
            sorted[k] = arr[i];
            i++;
        } else {
            sorted[k] = arr[j];
            j++;
        }
        k++;
    }
    // 남은 데이터도 삽입
    if (i > mid) {
        for (int t = j; t <= n; t++) {
            sorted[k] = arr[t];
            k++;
        }
    } else {
        for (int t = i; t <= mid; t++) {
            sorted[k] = arr[t];
            k++;
        }
    }
    // 정렬된 배열을 삽입
    for (int t = m; t <= n; t++) {
        arr[t] = sorted[t];
    }
}

void mergeSort(int a[], int m, int n) {
    if (m < n) {
        int middle = (m + n) / 2;
        mergeSort(a, m, middle);
        mergeSort(a, middle + 1, n);
        merge(a, m, middle, n);
    }
}

int main() {
    int array[number] = {7,5,6,8,3,5,9,1};
    mergeSort(array, 0, number-1);
    for(int i = 0; i < number; i++){
        cout << array[i] <<", ";
    }
    cout << endl;
    return 0;
}
