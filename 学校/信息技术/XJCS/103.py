a = list(map(int, input().split()))
n = int(input())
for i in range(n):
  s = input()
  if (s[0] == '+'): a.insert(int(s[1]), int(s[2]))
  else:
    for j in range(int(s[2])): del a[int(s[1])]
  # print(a)
for i in range(len(a) - 1):
  print(a[i], end = ' ')
print(a[-1])