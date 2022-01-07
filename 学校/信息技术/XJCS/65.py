import math

n = int(input())
a = list(map(int, input().split()))

ans = a[0]

for i in a:
    ans = ans * i // math.gcd(ans, i)

print(ans)

