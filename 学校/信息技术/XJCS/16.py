def Print(q, hd, tl):
    #print(hd, tl)
    for i in range(hd, tl):
        print(q[i], end = ' ')
    if (hd <= tl):
        print(q[tl])
    else:
        print()

s = input()
q = list(range(30))
hd, tl = 0, -1
ans = ''
for i in s:
    #print(i)
    if i == '0':
        if hd <= tl:
            hd += 1
        ans += '0'
    elif tl - hd <= 3:
        tl += 1
        q[tl] = i
        ans += i
    else:
        tl += 1
        hd += 1
        Print(q, hd, tl - 1)
        q[tl] = i
        ans += '0' + i
    Print(q, hd, tl)
for i in range(hd, tl + 1):
    ans += '0'
    hd += 1
    Print(q, hd, tl)
print(str(ans))

