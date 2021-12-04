a = input()
b = hex(ord(a))
t = b[2]
b[2] = b[3]
b[3] = t
print(b)
