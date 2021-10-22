def quick_sort(arr, start, end):
    if start >= end:
        return

    pivot = start
    i = start + 1
    j = end

    while i <= j:
        while arr[pivot] >= arr[i] and i <= end:
            i += 1
        while arr[pivot] <= arr[j] and j > start:
            j -= 1

        if i > j:
            arr[pivot], arr[j] = arr[j], arr[pivot]
        else:
            arr[i], arr[j] = arr[j], arr[i]

    quick_sort(arr, start, j - 1)
    quick_sort(arr, j + 1, end)


num_arr = [5, 3, 1, 7, 9, 10, 0]

quick_sort(num_arr, 0, len(num_arr) - 1)

print(num_arr)
