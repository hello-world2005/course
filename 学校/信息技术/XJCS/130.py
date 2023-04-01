from queue import Queue

n, m = map(int, input().split())
map = [[1 for j in range(m)] for i in range(n)]
vis = [[False for j in range(m)] for i in range(n)]
stp = [[0 for j in range(m)] for i in range(n)]
stpp = [[0 for j in range(m)] for i in range(n)]
x1, y1, x2, y2 = 0, 0, 0, 0
for i in range(n):
  s = input()
  for j in range(m):
    if (s[j] == '@'): x1, y1 = i, j
    if (s[j] == '&'): x2, y2 = i, j
    if (s[j] == '#'): map[i][j] = 0
    if (s[j] == 'F'): map[i][j] = 2
q = Queue()
q.put((x1, y1, 0))
vis[x1][y1] = True
dx = [-1, 0, 0, 1]
dy = [0, -1, 1, 0]
while (not q.empty()):
  u = q.get()
  x, y = u[0], u[1]
  s = u[2]
  stp[x][y] = s
  for i in range(4):
    _x = x + dx[i]
    _y = y + dy[i]
    if (_x >= 0 and _x < n and _y >= 0 and _y < m and not vis[_x][_y] and map[_x][_y]):
      vis[_x][_y] = True
      q.put((_x, _y, s + 1))
vis = [[False for j in range(m)] for i in range(n)]
q.put((x2, y2, 0))
vis[x2][y2] = True
while (not q.empty()):
  u = q.get()
  x, y = u[0], u[1]
  s = u[2]
  stpp[x][y] = s
  for i in range(4):
    _x = x + dx[i]
    _y = y + dy[i]
    if (_x >= 0 and _x < n and _y >= 0 and _y < m and not vis[_x][_y] and map[_x][_y]):
      vis[_x][_y] = True
      q.put((_x, _y, s + 1))
minn = 100000
for i in range(n):
  for j in range(m):
    if (map[i][j] == 2 and stp[i][j] != 0 and stpp[i][j] != 0 
          and stp[i][j] + stpp[i][j] < minn): minn = stp[i][j] + stpp[i][j]
if (minn == 100000): print('V wo 50')
else: print(minn)
