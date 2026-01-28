class ReverseWords:
    def reverse(self, s):
        return " ".join(s.split()[::-1])


s = input("Enter a sentence: ")
obj = ReverseWords()
print("Reversed sentence:")
print(obj.reverse(s))
