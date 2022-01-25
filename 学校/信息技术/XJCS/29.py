import io
import os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n = int(str(input())[2:-3])
t, k = list(range(n)), list(range(n))
nat = [[] for i in range(n)]
hd = 0
cnt = {}
for i in range(n):
    s = str(input())[2:-3].split(' ')
    #print(s)
    # print(s)
    t[i], k[i] = map(int, s[0:2])
    nat[i] = list(map(int, s[2:]))
    for j in nat[i]:
        # print('+', j)
        if (not(j in cnt)):
            cnt[j] = 1
        else:
            cnt[j] += 1
    pre = max(t[i] - 86400, 0)
    while (t[hd] <= pre):
        for j in nat[hd]:
            cnt[j] -= 1
            if (cnt[j] == 0):
                cnt.pop(j)
        hd += 1
    print(len(cnt))
        

