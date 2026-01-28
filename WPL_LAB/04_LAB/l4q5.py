class PairSum:
    def find(self, nums, target):
        d = {}
        for i in range(len(nums)):
            if target - nums[i] in d:
                return d[target - nums[i]] + 1, i + 1
            d[nums[i]] = i


nums = list(map(int, input("Enter numbers separated by space: ").split()))
target = int(input("Enter target sum: "))

p = PairSum()
i, j = p.find(nums, target)

print("Indices:", i, j)
