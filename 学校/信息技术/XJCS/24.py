s = input()
a = 0
flag = 0
for i in s:
    if i == '(':
        a += 1
    elif i == ')':
        a -= 1
    if a < 0:
        print('YES')
        flag = 1
        break
if a and not flag:
    print('YES')
elif not flag:
    print('NO')