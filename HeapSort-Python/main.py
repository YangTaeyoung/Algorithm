def make_heap(arr: list):
    if len(arr) == 0:
        return []

    for i in range(len(arr) // 2, len(arr)):
        child = i
        parent = child // 2

        while True:
            if arr[parent] < arr[child]:
                temp = arr[parent]
                arr[parent] = arr[child]
                arr[child] = temp
            child = parent
            parent = parent // 2
            if child <= 0:
                break
    return arr


def heap_sort(heap: list):
    n = len(heap)
    for i in range(n - 1, 0, -1):
        #  첫 요소랑 마지막 요소 바꾸기
        root = 0
        child = root * 2 + 1
        heap[i], heap[root] = heap[root], heap[i]

        while True:
            if child >= i:
                break
            if heap[child] < heap[child + 1] and child + 1 < i: # 자식을 옆으로 옮겨주는 부분.
                child += 1
            if heap[child] > heap[root]:  # 자식이 부모보다 큰 경우
                heap[child], heap[root] = heap[root], heap[child]
            root = child
            child = child * 2 + 1
    return heap

arr = []
for i in range(int(input())):
    arr.append(int(input()))

for num in heap_sort(make_heap(arr)):
    print(num)