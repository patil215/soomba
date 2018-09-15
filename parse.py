f = open('signals_left.txt')
import re

lines = []
for line in f:
    lines.append(line)

nums = []
nums.append(3000)
nums.append(3000)

rounds = [500, 1500]

def pick(options, value):
    best = 10000000
    bestOpt = 100000
    for opt in options:
        if abs(value - opt) < best:
            best = abs(value - opt)
            bestOpt = opt
    return bestOpt

for line in lines[1:-1]:
    keys = line.split()
    for i in range(4):
        token_a = keys[i * 2]
        token_b = keys[(i * 2) + 1]
        token_a = re.sub("[0-9]*:m", "", token_a)
        token_b = token_b[1:]
        print(token_a + " " + token_b)
        num_a = pick(rounds, int(token_a))
        num_b = pick(rounds, int(token_b))
        nums.append(num_a)
        nums.append(num_b)
nums.append(500)

print(nums)
print(len(nums))

print "unsigned int data = {",
for num in nums:
    print num,
    print ",",
print("}")
