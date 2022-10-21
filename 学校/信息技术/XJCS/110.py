s=input()
q=list(range(len(s)))
h,t=0,0
for i in s:
  if (i.isalpha()):q[t]=i;t+=1
  elif (h<t):h+=1
  for j in range(h,t):print(q[j],end=' ')
  print()