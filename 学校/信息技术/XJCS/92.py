n, x, y = map(int, input().split())
q = min(x, y, n - x + 1, n - y + 1)
if x <= y:
    ans = q * (4 * (n - 1) - 4 * q) + 10 * q - 4 * n - 3 + x + y
else:
    ans = q * (4 * n - 4 * q) + 2 * q + 1 - x - y
print(ans)