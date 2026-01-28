class Power:
    def pow(self, x, n):
        if n == 0:
            return 1
        if n < 0:
            return 1 / self.pow(x, -n)
        return x * self.pow(x, n - 1)


x = float(input("Enter value of x: "))
n = int(input("Enter value of n: "))

p = Power()
print("Result:", p.pow(x, n))
