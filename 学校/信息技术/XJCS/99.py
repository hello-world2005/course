s = input()

def Trans(c):
  a = ord(c)
  b = (a & 0b1111) ^ 0b1111
  b = ((b << 1) & 0b1111) + ((b & 0b1000) >> 3)
  return chr((a & 0b11110000) + b)

t = ''
for i in s:
  t += Trans(i)

print(t)
