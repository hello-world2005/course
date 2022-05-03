import io
import os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

sum=int(input())
for i in range(sum):
    n=int(input())
    for j in range(n-1):
        c=input()
    if n%2==0:
        print('xzh')
    else:
        print('zc')
        