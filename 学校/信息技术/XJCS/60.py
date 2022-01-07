s = input()
ans = 0
for i in s:
  if i == 'A':
    ans += 10
  elif i == 'B':
    ans += 9
  elif i == 'C':
    ans += 7
  else:
    ans += 4
print(ans)