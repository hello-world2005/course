s = input()
ans = ''
for i in range(len(s)):
  flag = False
  for j in range(i):
    if (s[i] == s[j]):
      flag = True
  if flag == False:
    ans += s[i]
print(ans)