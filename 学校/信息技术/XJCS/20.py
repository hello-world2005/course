s = input().split(',')
a, b = float(s[0]), int(s[1])
if b < 2000:
    print('%.2f' % a)
elif b < 4000:
    print('%.2f' % (a * 0.9))
elif b < 6000:
    print('%.2f' % (a * 0.8))
elif b < 8000:
    print('%.2f' % (a * 0.7))
else:
    print('%.2f' % (a * 0.6))