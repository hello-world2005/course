n, m = map(int, input().split())
a = [[0 for j in range(n)] for i in range(m)]
for i in range(n):
    s = list(map(int, input().split()))
    for j in range(m):
        a[j][i] = s[j]
for i in range(m):
    a[i].sort()
    s=0
    for j in range(1,n-1):
        s+=a[i][j]
    a[i][0]=s//(n-2)
for i in range(m):
    print(i+1,a[i][0])