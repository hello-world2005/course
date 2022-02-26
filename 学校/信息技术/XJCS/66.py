a, b = int(input()), int(input())
ans = []
def Prime(x):
    # print(int(x**0.5))
    for i in range(2, int(x**0.5) + 1):
        if (x % i == 0):
            return False
    return x != 1
for i in range(a, b + 1):
    if (Prime(i)):
        ans.append(i)
for i in range(len(ans) - 1):
    print(ans[i], end = ' ')
print(ans[-1])