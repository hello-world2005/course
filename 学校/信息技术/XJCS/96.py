a = list(map(int, input().split()))
f0 = False; f1 = False; lst = 0; ans = 0; i = 0
while (i < len(a)):
  j = i
  while (j < len(a) and a[j] == a[i]): j += 1
  ans += min(lst, j - i)
  lst = j - i
  i = j
print(ans)
