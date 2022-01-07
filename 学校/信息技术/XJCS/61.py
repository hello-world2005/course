s = input()
p0 = s.find('C')
p1 = s.find('H')
p2 = s.find('O')
p3 = len(s)
ans = 0
if (s[p0 + 1:p1] != ''):
  ans += 12 * int(s[p0 + 1:p1])
else:
  ans += 12
if (s[p1 + 1:p2] != ''):
  ans += int(s[p1 + 1:p2])
else:
  ans += 1
if (s[p2 + 1:p3] != ''):
  ans += 16 * int(s[p2 + 1:p3])
else:
  ans += 16
print(ans)
