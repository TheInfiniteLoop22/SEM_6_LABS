n = int(input("Enter number of words: "))
words = []

for i in range(n):
    words.append(input("Enter word: "))

words.sort()

print("Words in alphabetical order:")
for w in words:
    print(w)
