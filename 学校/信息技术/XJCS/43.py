maze = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
        [0, 1, 1, 0, 1, 1, 1, 0, 1, 0], 
        [0, 1, 1, 0, 1, 1, 1, 0, 1, 0], 
        [0, 1, 1, 1, 0, 0, 0, 1, 1, 0], 
        [0, 1, 0, 0, 0, 1, 1, 1, 1, 0], 
        [0, 1, 1, 1, 0, 1, 1, 1, 1, 0], 
        [0, 1, 0, 1, 1, 1, 0, 1, 1, 0], 
        [0, 1, 0, 0, 0, 1, 0, 0, 1, 0], 
        [0, 0, 1, 1, 1, 1, 1, 1, 1, 0], 
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
        
flag = False

DX = [-1, 0, 0, 1]
DY = [0, -1, 1, 0]

vis = [[False for i in range(10)] for i in range(10)]

def Dfs(x, y, _x, _y):
  # print(x, y)
  if (x == _x and y == _y):
    global flag
    flag = True
    # print('Hey')
    return
  for i in range(4):
    for j in range(4):
      dx = x + DX[i]
      dy = y + DY[j]
      # print(dx, dy, maze[dx][dy], vis[dx][dy])
      if (dx > -1 and dx < 10 and dy > -1 and dy < 10 and maze[dx][dy] == 1 and vis[dx][dy] == False):
        vis[dx][dy] = True
        Dfs(dx, dy, _x, _y)

s = list(map(int, input().split()))
x1, y1 = s[0], s[1]
s = list(map(int, input().split()))
x2, y2 = s[0], s[1]
vis[x1][y1] = True

Dfs(x1, y1, x2, y2)

if (maze[x1][y1] == 0 or maze[x2][y2] == 0):
  flag = False

if (flag):
  print('Yes')
else:
  print('No')
