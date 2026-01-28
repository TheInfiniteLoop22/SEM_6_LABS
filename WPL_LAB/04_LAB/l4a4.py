class ValidParentheses:
    def is_valid(self, s):
        stack = []
        mp = {')': '(', '}': '{', ']': '['}
        for ch in s:
            if ch in mp.values():
                stack.append(ch)
            else:
                if not stack or stack.pop() != mp.get(ch):
                    return False
        return not stack


s = input("Enter bracket string: ")
obj = ValidParentheses()

if obj.is_valid(s):
    print("Valid parentheses string")
else:
    print("Invalid parentheses string")
