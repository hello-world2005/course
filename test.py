s = list(range(1, 10))
tar = int(input())
tot = 0

def Dfs(dep):
  # print(dep, s)
  if (dep == 9):
    st = ''
    for i in s:
      if (i > 0):
        st += chr(i + 48)
      elif (i == -1):
        st += '+'
      else:
        st += '-'
    if (eval(st) == tar):
      print(st)
      global tot
      tot += 1
    return
  Dfs(dep + 1)
  p = 0
  for i in range(len(s)):
    if (s[i] == dep): p = i
  p += 1
  # print(p)
  s.insert(p, -1)
  Dfs(dep + 1)
  s.pop(p)
  s.insert(p, -2)
  Dfs(dep + 1)
  s.pop(p)

Dfs(1)
print(tot)
