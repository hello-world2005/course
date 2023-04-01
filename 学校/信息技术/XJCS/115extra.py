c1 = [0] * 100000
c2 = [0] * 100000

import bisect as bi
n = int(input())
a = list(map(int,input().split()))
b = list(map(int,input().split()))
aa = sorted(a)
bb = sorted(b)
aa.append(10000000000)
bb.append(10000000000)
sum1 = sum2 = 0
for i in range(n):
    pos = bi.bisect_left(bb, aa[i])
    sum1 += n - pos
    if bb[pos] == aa[i]:
        sum1 -= 1
for i in range(n):
    pos = bi.bisect_left(aa, bb[i])
    sum2 += n - pos
    if aa[pos] == bb[i]:
        sum2 -= 1
ans1 = min(sum1, sum2)
sum1 = sum2 = 0
for i in range(n):
    x = bi.bisect_left(aa, a[i]) + 1
    while x <= n:
        sum1 += c1[x]
        x += (x & -x)
    x = bi.bisect_left(aa, a[i]) + 1
    while x > 0:
        c1[x] += 1
        x -= (x & -x)
sum1 = n * (n - 1) // 2 - sum1
for i in range(n):
    x = bi.bisect_left(bb, b[i]) + 1
    while x <= n:
        sum2 += c2[x]
        x += (x & -x)
    x = bi.bisect_left(bb, b[i]) + 1
    while x > 0:
        c2[x] += 1
        x -= (x & -x)
sum2 = n * (n - 1) // 2 - sum2
ans2 = 10000000000
#print(ans1)
for i in range(n):
    pos1 = bi.bisect_left(aa, a[i])
    pos2 = bi.bisect_left(bb, b[i])
    sum1 += pos1 - (n - pos1 - 1)
    sum2 += pos2 - (n - pos2 - 1)
    ans2 = min(ans2, sum1 + sum2)
print(ans1 + ans2)