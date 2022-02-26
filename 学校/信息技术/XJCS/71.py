s = input()
n = int(input())
ans = ''
for i in s:
    if (i >= 'a' and i <= 'z'):
        ans += (chr((ord(i) - n - 97) % 26 + 97))
    elif (i >= 'A' and i <= 'Z'):
        ans += (chr((ord(i) - n - 65) % 26 + 65))
    else:
        ans += (i)
print(ans)