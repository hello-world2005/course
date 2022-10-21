st = list(range(10010))
st[0] = 'http://www.acm.org/'
tp, tpp = 1, 1
while True:
  s = input().split()
  if (s[0] == 'QUIT'): break
  if (s[0] == 'VISIT'): st[tp] = s[1];print(s[1]);tp += 1;tpp = tp
  elif (s[0] == 'BACK'): print(st[tp - 2] if tp >= 2 else 'Ignored');tp = tp - 1 if tp >= 2 else tp
  else: print(st[tp] if tp != tpp else 'Ignored');tp = tp + 1 if tp < tpp else tp