li = list(map(int, input().split(' ')))
a, b = li[0], li[1]
sum, nsum = 0, 0
while a != b:
  if a >= 8 and a < 19:
    sum += 12
  else:
    nsum += 4
  a = (a + 1) % 24
if nsum > 10:
  nsum = 10
sum += nsum
if sum > 96:
  sum = 96
print(sum)
