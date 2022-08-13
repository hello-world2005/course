s = list(input())
op = input()

pos = []
st = []
ope = []

for i in range(len(op)):
  if (i >= 1 and op[i - 1].isnumeric() and op[i].isalpha()):
    stb = i
    pos.append(int(op[sta + 1:i]))
  if (i >= 1 and op[i - 1].isalpha() and (op[i] == '+' or op[i] == '-')):
    st.append(op[stb:i])
  if (op[i] == '+' or op[i] == '-'):
    sta = i
    ope.append(op[i])
st.append(op[stb:len(op)])

pos.reverse()
st.reverse()
ope.reverse()

for i in s:
  print(i, end = '')

for i in range(len(pos)):
  print('-->', end = '')
  if (ope[i] == '-'):
    st[i] = list(st[i])
    st[i].reverse()
    for j in st[i]:
      s.insert(pos[i], j)
  else:
    l = len(st[i])
    while (l > 0):
      l -= 1
      del s[pos[i]]
  for i in s:
    print(i, end = '')

print()
