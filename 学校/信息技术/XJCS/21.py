stk = list(range(1000))
tp = 0

s = input().split()

for i in s:
    if (i.isdigit()):
        tp += 1
        stk[tp] = int(i)
    else:
        a = stk[tp]
        tp -= 1
        b = stk[tp]
        if (i == '+'):
            stk[tp] = b + a
        if (i == '-'):
            stk[tp] = b - a
        if (i == '*'):
            stk[tp] = b * a
        if (i == '/'):
            stk[tp] = b / a

print(stk[tp])