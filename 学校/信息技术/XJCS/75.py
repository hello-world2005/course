for i in range(1, 10):
    ans = ''
    for j in range(1, i + 1):
        x = i * j
        ans += str(j) + '*' + str(i) + '='
        if (x < 10):
            ans += ' ' + str(x)
        else:
            ans += str(x)
        if (j != i):
            ans += ' '
    print(ans)

