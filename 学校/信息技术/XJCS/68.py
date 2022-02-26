s = int(input())
for i in range(s // 5 + 1):
    s1 = s - i * 5
    for j in range(s1 // 3 + 1):
        s2 = s1 - j * 3
        if (i * 5 + j * 3 <= s and i + j + s2 * 3 == s):
            print(i, j, s2 * 3)