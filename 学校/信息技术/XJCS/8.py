s = input()
s1 = s.split(' ')
s = input()
s2 = s.split(' ')

ply1 = []
ply2 = []
ply = []

for i in range(110):
    ply1.append(0)
    ply2.append(0)
    ply.append(0)

for i in range(len(s1)):
    if i % 2 == 0:
        ply1[int(s1[i + 1])] += int(s1[i])
for i in range(len(s2)):
    if i % 2 == 0:
        ply2[int(s2[i + 1])] += int(s2[i])

for i in range(110):
    ply[i] = ply1[i] + ply2[i]

for i in range(101):
    j = 100 - i
    if (ply[j] != 0):
        print('[' + str(ply[j]) + ' ' + str(j) + ']', end = '')