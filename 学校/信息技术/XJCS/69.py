a, b, c = map(int, input().split())
flag = False
for i in range(c // a + 1):
    if (i * a <= c and (c - i * a) % b == 0):
        print('Yes')
        flag = True
        break
if (not flag):
    print('No')