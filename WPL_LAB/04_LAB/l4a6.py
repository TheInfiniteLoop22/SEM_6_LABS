class Circle:
    def area(self, r):
        return 3.14 * r * r

    def perimeter(self, r):
        return 2 * 3.14 * r


r = float(input("Enter radius of the circle: "))
c = Circle()

print("Area of circle:", c.area(r))
print("Perimeter of circle:", c.perimeter(r))
