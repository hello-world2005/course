s = input().split(' ')
a, b = int(s[0]), int(s[-1])
sum = 0
while sum <= b:
  sum += a
  a += 1
print(sum - a + 1, a - 2)