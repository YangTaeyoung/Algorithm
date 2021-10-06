#include <iostream>

using namespace std;

// 최대 힙 구조 만들기.
int* makeHeap(int* numArr, int n){
    for (int i = 1; i < n; i++) {
        int c = i;
        do {
            int root = (c - 1) / 2;
            if (numArr[root] < numArr[c]) {
                int temp = numArr[root];
                numArr[root] = numArr[c];
                numArr[c] = temp;
            }
            c = root;
        } while (c != 0);
    }
    return numArr;
}

int* heapSort(int* heap, int n){
    // 크기를 줄여가며 반복적으로 힙 구성.
    for (int i = n - 1; i >= 0; i--) {
        // 루트 노드와 마지막 노드 바꾸기
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;
        int root = 0;
        int c = 1;
        do {
            c = 2 * root + 1;
            // 자식 중에 더 큰 값 찾기
            if (heap[c] < heap[c + 1] && c < i - 1) {
                c++;
            }
            if (heap[root] < heap[c] && c < i) {
                int temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            root = c;
        } while (c < i);
    }
    return heap;
}

int printArr(int* arr, int n){
    cout << "[";
    for(int i = 0; i < n; i++){
        cout << arr[i];
        if(i != n-1){
            cout << ",";
        }
    }
    cout << "]" << endl;
}
int main() {
    cout << "----- 정렬 전 -----" << endl;
    int arr[] = {5,2,1,5,6,7,8,3,16};
    printArr(arr,9);
    cout << "----- 정렬 후 -----" << endl;
    printArr(heapSort(makeHeap(arr,9), 9),9);

    return 0;
}
