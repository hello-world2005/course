s = list(input().split())

stk1, stk2 = list(range(1000)), list(range(1000))
tp1, tp2 = 0, 0

tp1 += 1
stk1[tp1] = '#'

pri = {'+': 1, '-': 1, '*': 2, '/': 2, '#': 0, '(': 3}

for i in s:
    if (i.isdigit()):
        tp2 += 1
        stk2[tp2] = i
    else:
        if (i == '('):
            tp1 += 1
            stk1[tp1] = i
        elif (i == ')'):
            while (stk1[tp1] != '('):
                tp2 += 1
                stk2[tp2] = stk1[tp1]
                tp1 -= 1
            tp1 -= 1
        else:
            if (stk1[tp1] == '('):
                tp1 += 1
                stk1[tp1] = i
            else:
                while (pri[stk1[tp1]] >= pri[i] and stk2[tp2] != '('):
                    tp2 += 1
                    stk2[tp2] = stk1[tp1]
                    tp1 -= 1
                tp1 += 1
                stk1[tp1] = i

while (stk1[tp1] != '#'):
    tp2 += 1
    stk2[tp2] = stk1[tp1]
    tp1 -= 1

for i in range(1, tp2):
    print(stk2[i], end = '')
print(stk2[tp2])
