def make_heap(arr: list):
    for i in range(len(arr)):
        child = i
        while child != 0:
            parent = (child - 1) // 2
            if arr[parent] < arr[child]:
                arr[parent], arr[child] = arr[child], arr[parent]
            child = parent



def heap_sort(heap: list):
    make_heap(heap)
    for i in range(len(heap) - 1, 0, -1):
        #  첫 요소랑 마지막 요소 바꾸기
        root = 0
        child = 0
        heap[i], heap[root] = heap[root], heap[i]

        while child < i:
            child = child * 2 + 1
            if child < i-1 and heap[child] < heap[child + 1]:  # 자식을 옆으로 옮겨주는 부분.
                child += 1
            if child < i and heap[child] > heap[root]:  # 자식이 부모보다 큰 경우
                heap[child], heap[root] = heap[root], heap[child]
            root = child


arr = []
for i in range(int(input())):
    arr.append(int(input()))
heap_sort(arr)

for num in arr:
    print(num)
