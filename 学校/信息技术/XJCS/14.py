s = input()

ans = True

for i in range(len(s)):
    if (s[i] != '0' and s[i] != '1' and s[i] != '2' and s[i] != '3' and s[i] != '4' and s[i] != '5' and s[i] != '6' and s[i] != '7' and s[i] != '8' and s[i] != '9'):
        ans = False

for i in range(len(s)):
    if s[i] != s[len(s) - i - 1]:
        ans = False

print(ans)