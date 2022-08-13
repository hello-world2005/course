s = input()
ss = input()
a = []
ans = []

pre = 0
for i in range(len(s)):
  if (not s[i].isalpha()): a.append(s[pre:i]); pre = i + 1
  flag = False
  if (len(a) and a[-1] == ss):
    ans.append(i - len(a[-1]))
    del a[-1]
    flag = True
  if (not s[i].isalpha() and not flag): a.append(s[i])
# for i in range(len(a) - 1, 0, -1):
#   # print(a[i - 1], a[i], sep = '#')
#   if ((not a[i - 1].isspace()) and (not a[i].isspace())): del a[i]
for i in a: print(i, end = '')
print()
if (len(ans)):
  for i in ans: print(i, end = ' ')
  print()
else:
  print('未出现！')
