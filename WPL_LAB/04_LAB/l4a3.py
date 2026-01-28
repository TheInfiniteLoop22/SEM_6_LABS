r1, c1 = map(int, input("Enter rows and columns of first matrix: ").split())
a = []

print("Enter elements of first matrix:")
for i in range(r1):
    a.append(list(map(int, input().split())))

r2, c2 = map(int, input("Enter rows and columns of second matrix: ").split())
b = []

print("Enter elements of second matrix:")
for i in range(r2):
    b.append(list(map(int, input().split())))

res = [[0] * c2 for _ in range(r1)]

for i in range(r1):
    for j in range(c2):
        for k in range(c1):
            res[i][j] += a[i][k] * b[k][j]

print("Resultant matrix:")
for row in res:
    print(*row)
