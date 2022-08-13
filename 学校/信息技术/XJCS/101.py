s = input()
key = input()
flag = True
while (flag):
  flag = False
  a = [False for i in range(len(s))]
  i = 0
  while (i < len(s) - len(key)):
    if (s[i:i + len(key)] == key):
      for j in range(i, i + len(key)): a[j] = True
      # print(i, a, s[i:i + len(key)])
      i = i + len(key) - 1
      flag = True
      # print(i)
    i += 1
  i = len(s) - len(key)
  # print(s)
  while (i < len(s)):
    # print(s[i:len(s)] + s[0:len(key) - len(s) + i], i)
    if (s[i:len(s)] + s[0:len(key) - len(s) + i] == key):
      _ = False
      for j in range(i, len(s)):
        if (a[j]): _ = True
      for j in range(0, i + len(key) - len(s)):
        if (a[j]): _ = True
      if (_): i += 1;continue
      for j in range(i, len(s)): a[j] = True
      for j in range(0, i + len(key) - len(s)): a[j] = True
      flag = True
      break
    i += 1
  # print(a)
  t = ''
  for i in range(len(s)):
    if (a[i] == False): t += s[i]
  s = t
print(s)
