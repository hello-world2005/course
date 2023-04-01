import math
n, q1, q2 = map(int,input().split())
a, b, sum, mod, tot = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1), 1 << 32, 0
for k in range(q1):
    s, x = map(int,input().split())
    rec, i = [], 2
    while i * i <= s:
        if s % i == 0:
            rec.append(i)
        while s % i == 0:
            s //= i
        i += 1
    if s != 1:
        rec.append(s)
    for i in range(1 << len(rec)):
        cur, cnt = 1, 0
        for j in range(len(rec)):
            if i >> j & 1:
                cur *= rec[j]
                cnt += 1
        if cnt % 2 == 0:
            a[cur] = (a[cur] + x) % mod
        else:
            a[cur] = (a[cur] - x) % mod
print(a)
for i in range(1, n + 1):
    for j in range(i, n + 1, i):
        sum[j] = (sum[j] + a[i]) % mod
for i in range(1, n + 1):
    a[i] = 0
    for j in range(i, n + 1, i):
        a[i] = (a[i] + sum[j]) % mod
print(a)
for k in range(q2):
    s, ans = int(input()), 0
    rec, i = [], 2
    while i * i <= s:
        if s % i == 0:
            rec.append(i)
        while s % i == 0:
            s //= i
        i += 1
    if s != 1:
        rec.append(s)
    for i in range(1 << len(rec)):
        cur, cnt = 1, 0
        for j in range(len(rec)):
            if i >> j & 1:
                cur *= rec[j]
                cnt += 1
        if cnt % 2 == 0:
            ans = (ans + a[cur]) % mod
        else:
            ans = (ans - a[cur]) % mod
    print(ans)