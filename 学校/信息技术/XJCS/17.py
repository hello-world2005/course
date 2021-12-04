a = int(input())
if a % 400 != 0 and a % 100 == 0:
  print('No')
elif a % 4 == 0:
  print("Yes");
else:
  print('No')