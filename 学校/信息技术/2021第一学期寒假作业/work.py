f = open('pt.txt', mode = 'r')
g = open('out.txt', mode = 'w')
s = f.read().split('), (')
print(s)
for i in s:
  g.write('t.goto(' + i + ')\n')
