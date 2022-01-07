a = [[0 for i in range(26)] for j in range(26)]
for i in range(26):
  for j in range(26):
    a[i][j] = chr((i + j) % 26 + 65)
s1 = input()
s2 = input().upper()
ans = '密文是:'
j = 0
for i in s1:
  if (ord(i) < 96):
    ans += a[ord(i) - 65][ord(s2[j]) - 65]
  else:
    ans += chr(ord(a[ord(i) - 97][ord(s2[j]) - 65]) + 32)
  j = (j + 1) % len(s2)
print(ans)