n = int(input())
m = 0

while n != 1:
    if n % 2 == 1:
        m = n * 3 + 1
        print('%d*3+1=%d' % (n, m))
    else:
        m = n // 2
        print('%d//2=%d' % (n, m))
    n = m

print('End')