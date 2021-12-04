n = int(input())
li = list(map(int, input().split(' ')))
li.sort()
for i in li:
  if i != li[-1]:
    print(i, end = ' ')
  else:
    print(i)
ans = []
for i in range(n):
  if not (i in li):
    ans.append(i)
for i in ans:
  if i != ans[-1]:
    print(i, end = ' ')
  else:
    print(i)
