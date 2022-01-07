s = input().split()
a = int(s[0])
b = int(s[1])

def Check(a):
    if (a == 2):
        return True
    for i in range(2, a):
        if (a % i == 0):
            return False
    return True

ans = list()
for i in range(a, b + 1):
    if (Check(i)):
        ans.append(i)

for i in range(len(ans) - 1):
    print(ans[i], end = ' ')
print(ans[-1])