s = input()
n = int(input())
ans = []
for i in s:
    ans.append(ord(i) ^ n)
for i in range(len(ans) - 1):
    print(bin(ans[i])[2:], end = ' ')
print(bin(ans[-1])[2:])