def merge(arr1: list, arr2: list):
    sorted = list()
    while len(arr1) != 0 and len(arr2) != 0:
        if arr1[0] >= arr2[0]:
            sorted.append(arr2.pop(0))
        else:
            sorted.append(arr1.pop(0))
    if len(arr1) == 0:
        sorted = sorted + arr2
    else:
        sorted = sorted + arr1
    return sorted

def merge_sort(arr):
    if len(arr) > 1:
        arr1 = merge_sort(arr[:len(arr)//2])
        arr2 = merge_sort(arr[len(arr)//2:])
        return merge(arr1, arr2)
    else:
        return arr

n = int(input())
num_list = list()
for i in range(n):
    num_list.append(int(input()))
num_list = merge_sort(num_list)

for num in num_list:
    print(num)
