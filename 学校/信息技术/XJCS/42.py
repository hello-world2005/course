def Bitch(n, a, b, c):
  if (n == 1):
    print(a, '->', n, '->', c)
    return
  Bitch(n - 1, a, c, b)
  print(a, '->', n, '->', c)
  Bitch(n - 1, b, a, c)

s = input().split()
Bitch(int(s[0]), s[1], s[2], s[3])