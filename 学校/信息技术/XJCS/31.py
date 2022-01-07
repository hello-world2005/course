s = input()
n = int(input())
vis = [False for i in range(len(s))]
for i in range(len(s) - 1):
  if (ord(s[i]) > ord(s[i + 1]) and n > 0):
    vis[i] = True
    n -= 1
for i in range(len(s) - 1, len(s) - n - 1, -1):
  vis[i] = True
for i in range(len(s)):
  if (not vis[i]):
    print(s[i], end = '')
print()
