n=int(input())
a=[[0 for j in range(n+1)] for i in range(n+1)]
a[0][1]=1
for i in range(1,n+1):
  for j in range(1,i+1):a[i][j]=a[i-1][j-1]+a[i-1][j]
  for j in range(1,i):print(a[i][j],end = ' ')
  print(a[i][i])