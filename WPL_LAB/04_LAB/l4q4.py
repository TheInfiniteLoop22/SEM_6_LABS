class Subsets:
    def get_subsets(self, nums):
        res = []
        n = len(nums)
        for i in range(1 << n):
            cur = []
            for j in range(n):
                if i & (1 << j):
                    cur.append(nums[n - 1 - j])
            res.append(cur)
        return res


nums = list(map(int, input("Enter distinct integers separated by space: ").split()))
obj = Subsets()
print("All possible subsets:")
print(obj.get_subsets(nums))
