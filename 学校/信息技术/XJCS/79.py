n, m = map(int, input().split())
s = [[] for i in range(n)]
su = ['Chinese', 'Math', 'English', 'Physics', 'Chemistry', 'Biology', 'Politics', 'History', 'Geography', 'Technology']
for i in range(n):
  s[i] = list(map(int, input().split()))
for j in range(m):
  idx = 0
  maxn = s[0][j]
  for i in range(n):
    if (s[i][j] > maxn):
      idx = i
      maxn = s[i][j]
  print(su[j], chr(idx + 65), maxn)