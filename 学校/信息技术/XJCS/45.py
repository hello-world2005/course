def Dfs(frm, cho, dep, n, ans):
   # print(frm, cho, dep, n)
   if (dep == n):
      if (len(cho) != n):
         print(cho, end = ', ')
      else:
         print(cho, end = ']')
      return
   Dfs(frm, cho, dep + 1, n, ans)
   cho.append(frm[dep])
   Dfs(frm, cho, dep + 1, n, ans)
   cho.pop()

s = input()
li = s.split(',')
ans = list()
print('[', end ='')
Dfs(li, list(), 0, len(li), ans)

