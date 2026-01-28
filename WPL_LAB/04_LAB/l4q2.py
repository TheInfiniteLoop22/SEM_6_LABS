def binary_search(arr, l, r, x):
    if l > r:
        return -1
    m = (l + r) // 2
    if arr[m] == x:
        return m
    if arr[m] > x:
        return binary_search(arr, l, m - 1, x)
    return binary_search(arr, m + 1, r, x)


n = int(input("Enter number of elements: "))
arr = list(map(int, input("Enter sorted elements: ").split()))
x = int(input("Enter element to search: "))

pos = binary_search(arr, 0, n - 1, x)

if pos == -1:
    print("Element not found")
else:
    print("Element found at index", pos)
