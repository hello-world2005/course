a = int(input())
b = int(input())
c = int(input())

ans = 0

for i in range(a, b + 1, c):
    ans += i

print(ans)
