import io
import os
import sys
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

class DoubleNode(object):
  def __init__(self, data):
    self.data = data
    self.nxt = None
    self.pre = None

class DoubleList(object):
  def __init__(self):
    self.hd = DoubleNode(None)
    self.tl = DoubleNode(None)
    self.hd.nxt = self.tl
    self.tl.pre = self.hd

  def empty(self):
    return self.hd.nxt == self.tl
  
  def append(self, item):
    node = DoubleNode(item)
    if (self.empty()):
      self.hd.nxt = node
      node.pre = self.hd
      self.tl.pre = node
      node.nxt = self.tl
      return
    cur = self.tl.pre
    cur.nxt = node
    node.pre = cur.nxt
    self.tl.pre = node
    node.nxt = self.tl
  
  def get(self, index):
    return self.hd.nxt.data
  
  def delete(self, index):
    cur = self.hd.nxt
    cur.nxt.pre = self.hd
    cur.pre.nxt = cur.nxt

  def add(self, item):
    cur = self.tl.pre
    cur.nxt = item.hd.nxt
    item.hd.nxt.pre = cur
    self.tl.pre = item.tl.pre
    item.tl.pre.nxt = self.tl
  
  def Get(self):
    cur = self.hd
    rt = list()
    if (self.empty()):
      return
    while (cur.nxt != self.tl):
      cur = cur.nxt
      # print(cur.data.tot, fuck_py[cur.data.tot])
      # print(cur.data.tot, fuck_py[cur.data.tot].data())
      rt.append(fuck_py[cur.data.tot].get(0))
      fuck_py[cur.data.tot].delete(0)
    return rt
  
  def Merge(self):
    cur = self.hd
    pre = None
    if (self.empty()):
      return
    while (cur.nxt != self.tl):
      pre = cur
      cur = cur.nxt
      while (cur.nxt != self.tl and fuck_py[cur.data.tot].empty()):
        pre.nxt = cur.nxt
        cur.nxt.pre = pre
        cur = cur.nxt
      if (cur.nxt == self.tl and fuck_py[cur.data.tot].empty()):
        pre.nxt = self.tl
        self.tl.pre = pre
    cur = self.hd.nxt
    pre = self.hd
    if (self.empty()):
      return
    while (cur.nxt != self.tl):
      pre = cur
      cur = cur.nxt
      while (cur.nxt != self.tl and cur.data.kind == pre.data.kind):
        fuck_py[pre.data.tot].add(fuck_py[cur.data.tot])
        pre.nxt = cur.nxt
        cur.nxt.pre = pre
        cur = cur.nxt
      if (cur.nxt == self.tl and cur.data.kind == pre.data.kind):
        fuck_py[pre.data.tot].add(fuck_py[cur.data.tot])
        self.tl.pre = pre
        pre.nxt = self.tl

  def data(self):
    rt = list()
    cur = self.hd
    if (cur == None):
      return rt
    cur = cur.nxt
    while cur != None:
      rt.append(cur.data)
      cur = cur.nxt
    return rt

class Unknow(object):
  def __init__(self, kind, tot):
    self.kind = kind
    self.tot = tot

# n = input()
# print(n)

n = int(input())
s = str(input())[2:-3].split(' ')
# print(s)
# s = input().split(' ')
a = list(range(n))
for i in range(n):
  a[i] = int(s[i])

li = DoubleList()

now = 0
fuck_py = list()
# now_item.append(a[1])
fuck_py.append(DoubleList())
fuck_py[0].append(0)

for i in range(1, n):
  if (a[i] == a[i - 1]):
    # now_item.append(a[i])
    fuck_py[now].append(i)
  else:
    un = Unknow(a[i - 1], now)
    li.append(un)
    # print(now_item, fuck_py)
    # now_item.clear()
    now += 1
    fuck_py.append(DoubleList())
    fuck_py[now].append(i)
    # now_item.append(a[i])
un = Unknow(a[-1], now)
# now_item.append(a[-1])
li.append(un)
# fuck_py[now].append(n - 1)

# qwq = li.data()

# for i in qwq:
#   print('!', fuck_py[i.tot])

def Print(get):
  # print(get)
  for i in range(len(get) - 1):
    sys.stdout.write(str(get[i] + 1) + ' ')
  sys.stdout.write(str(get[-1] + 1) + '\n')

# tme = 0

while (not li.empty()):
  Print(li.Get())
  li.Merge()
  # tme += 1
  # print(tme)

# Print(li.Get())

