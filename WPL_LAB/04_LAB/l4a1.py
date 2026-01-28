n = int(input("Enter number of elements: "))
arr = list(map(int, input("Enter elements separated by space: ").split()))

if len(arr) != n:
    print("Error: Number of elements entered does not match")
else:
    m = arr[0]
    for x in arr[1:]:
        if x < m:
            m = x
    print("Smallest element:", m)
