class StringOps:
    def get_String(self):
        self.s = input("Enter a string: ")

    def print_String(self):
        print("Uppercase string:", self.s.upper())


obj = StringOps()
obj.get_String()
obj.print_String()
