t1=int(input())
t2=int(input())
if  t1 > t2  :    
    t1,t2=t2,t1
i=t1
print('摄氏温度    华氏温度')
while i <= t2  :  
    f=i*9/5+32    #摄氏温度转华氏温度
    print('  ',i,'     ',f)
    i += 1
