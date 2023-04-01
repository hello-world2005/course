import os
for cas in range(100):
  os.system('python gen.py')
  os.system('python std.py < .in > .out')
  os.system('time python std1.py < 1.in > .ans')
  if (os.system('fc .out .ans')):
    print('!')
    break
  else:
    print('suc', cas)
  break
