n = int(input())
qwq = input().split(' ')

ans = 0

for i in range(len(qwq)):
    if int(qwq[i]) > n:
        ans += 1
    else:
        n -= int(qwq[i])

print(ans)