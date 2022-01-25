a = int(input())
tot = 1e8
ans = 0
now = 0.2
while tot > 0:
    ans += 1
    tot -= now
    now *= a
print(ans)