import math

a = float(input())
b = float(input())
c = float(input())
if a + b > c and a + c > b and b + c > a:
    p = (a + b + c) / 2
    print('%.2f' % math.sqrt(p * (p - a) * (p - b) * (p - c)))
else:
    print('It is not a triangle.')

