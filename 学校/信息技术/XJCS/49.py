def Dfs(li, ed):
    n = len(li)
    if (ed == n):
        print(li)
        return
    for i in range(ed, n):
        li[i], li[ed] = li[ed], li[i]
        Dfs(li, ed + 1)
        li[i], li[ed] = li[ed], li[i]

a = input().split(',')
Dfs(a, 0)

