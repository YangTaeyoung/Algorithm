#include <iostream>
using namespace std;

int n = 10;
int data[10] = {1,10,5,4,2,7,8,6,3,9};
void printArr(int* arr, int n){
    cout << "[";
    for(int i = 0; i<n;i++){
        cout << arr[i];
        if (i != n-1){
            cout <<", ";
        }
    }
    cout << "]" << endl;
}
void quickSort(int* data, int start, int end){
    if(start >= end){
        return;
    }

    int key = start; // 피벗
    int i = start+1;
    int j = end;
    int temp;

    while(i <= j){ // i와 j가 엇갈릴 때까지 반복
        while(data[i] <= data[key] && i <= end) // 키 값보다 데이터가 큰 경우를 찾음 // 우측 그룹
        {
            i++;
        }
        while(data[j] >= data[key] && j > start) // 키 값보다 데이터가 작은 경우를 찾음
        {
            j--;
        }

        if(i > j){ // 데이터가 엇갈린 상태면 키 값과 교채
            temp = data[j];
            data[j] = data[key];
            data[key] = temp;
        }
        else // 데이터가 엇갈리지 않은 상태면 i값과 j값을 교체
        {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }


    }
    quickSort(data, start, j-1);
    quickSort(data, j+1, end);
}

int main() {
    cout << "======= 정렬 전 =======" << endl;
    printArr(data,n);
    quickSort(data, 0, n-1);
    cout << "======= 정렬 후 =======" << endl;
    printArr(data,n);
    return 0;
}
