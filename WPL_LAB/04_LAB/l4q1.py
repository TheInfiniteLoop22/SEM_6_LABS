inp = input("Enter input file name: ")
out = input("Enter output file name: ")

f = open(inp, "r")
data = f.read()
f.close()

rev = data[::-1]

f = open(out, "w")
f.write(rev)
f.close()

print("Reversed content:")
print(rev)
