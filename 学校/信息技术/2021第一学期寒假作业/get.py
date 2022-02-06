from turtle import TurtleScreen, TK

def Print(x, y):
  f.write('t.goto(' + str(x) + ', ' + str(y) + ')\n')

f = open('out.txt', 'w')
root = TK.Tk()
cv = TK.Canvas(root, width=500, height=500)
cv.pack()
sc = TurtleScreen(cv)
sc.bgpic('/Users/helloworld2005/Downloads/QQ20220201-0.gif')
for i in range(10000):
  sc.onscreenclick(Print)

TK.mainloop()
