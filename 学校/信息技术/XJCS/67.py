n = int(input())
for i in range(1, n + 1):
    x = 2 * i - 1
    y = 2 * n - 1
    for j in range((y - x) // 2):
        print(' ', end = '')
    for j in range(x):
        print('*', end = '')
    #for j in range((y - x) // 2):
    #    print(' ', end = '')
    print('')