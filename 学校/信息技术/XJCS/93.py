a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = []

i, j = 0, 0
for k in range(len(a) + len(b)):
  if (i < len(a) and j < len(b) and a[i] < b[j]):
    c.append(a[i])
    i += 1
  elif (i < len(a) and j < len(b) and b[j] < a[i]):
    c.append(b[j])
    j += 1
  elif (i < len(a)):
    c.append(a[i])
    i += 1
  else:
    c.append(b[j])
    j += 1

for i in range(len(c) - 1):
  print(c[i], end = ' ')
print(c[-1])
