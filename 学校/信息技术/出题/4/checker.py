import os
# for cas in range(100):
  # os.system('python gen.py')
os.system('time python std1.py < data/1.in > .out')
# os.system('time python std1.py < 1.in > .ans')
if (os.system('fc .out data/1.ans')):
  print('!')
else:
  print('?')
