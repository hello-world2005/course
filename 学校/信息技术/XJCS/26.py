s = input().split(' ')
n, m = int(s[0]), int(s[1])
k = int(input())
x, y = 0, 0
for i in range(k):
    print(x + 1, y + 1)
    x = (x + 1) % n
    y = (y + 1) % m