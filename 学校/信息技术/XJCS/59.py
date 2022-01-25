a = list(map(int, input().split(',')))
vis = list(range(1001))
buck = list(range(1001))
for i in range(1001):
    vis[i] = 0
    buck[i] = 0
for i in a:
    buck[i] += 1
ans = list()
for i in a:
    if vis[i]:
        continue
    ans.append(i)
    ans.append(buck[i])
    vis[i] = 1
for i in range(len(ans) - 1):
    print(ans[i], end = ' ')
print(ans[len(ans) - 1])
#fuck PE
