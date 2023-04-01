from random import randint as rdi
n=10;a=[];i=0
while i<=n-1:   #随机生成n个10-99之间的不重复的整数，存入列表a中
    x=rdi(10,99)          #1
    if x not in a:   #2
        a.append(x)
        i=i+1
print(a)
k=int(input("请输入要查找数的位次k:"))
low=high=a[0]         #3
for i in range(1,n):
    if a[i]<low:
        low=a[i]
    if a[i]>high:
        high=a[i]
while low<high:    #4
    m=(low+high)//2
    cnt=0
    for i in range(0,n):
        if a[i]>m:
            cnt+=1          #5
    if cnt>=k:
        low=m+1
    else:
        high=m
print("第",k,"大的整数是：",     low)   #6