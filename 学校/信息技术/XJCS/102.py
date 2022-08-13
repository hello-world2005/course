s = input()
vis = set()
tot = 0

for i in range(len(s)):
  for j in range(i, len(s) + 1):
    # if (s[i:j] in vis): continue
    # print(i, j, s[i:j])
    if (s[i:j] == ''): continue
    vis.add(s[i:j])
    print(s[i:j], end = ' ')
    tot += 1
print()
print(tot + 1)
