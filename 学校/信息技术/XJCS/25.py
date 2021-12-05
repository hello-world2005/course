n = int(input())
tp = -1
stk = list(range(n))
flag = False
ans = []
for i in range(n):
  s = input().split(' ')
  opt = s[0]
  if (opt == 'push'):
    a = int(s[1])
    tp += 1
    stk[tp] = a
  else:
    if (tp != -1):
      tp -= 1
      ans.append(stk[tp + 1])
    else:
      flag = True
if flag:
  print('error')
else:
  while (tp != -1):
    if (tp != 0):
      print(stk[tp], end = ' ')
    else:
      print(stk[tp])
    tp -= 1
