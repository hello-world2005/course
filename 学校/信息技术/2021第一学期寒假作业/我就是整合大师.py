from turtle import RawTurtle, TurtleScreen, TK
#from cyh

def tiger():
    t = RawTurtle(sc)
    #outline
    t.penup()
    t.goto(0,-10)
    t.pendown()
    t.pensize(4)
    t.fillcolor(1,0.65,0)
    t.begin_fill()
    t.forward(50)
    t.right(15)
    t.forward(57)
    t.circle(-50,77)
    t.left(20)
    t.circle(-100,25)
    t.left(60)
    t.circle(-30,120)
    t.left(18)
    t.circle(-200,10)
    t.left(19)
    t.circle(-27,90)
    t.left(5)
    t.circle(150,67)
    t.right(30)
    t.circle(-40,60)
    t.left(10)
    t.circle(-200,10)
    t.left(3)
    t.circle(-34,90)
    t.left(40)
    t.forward(25)
    t.circle(-60,40)
    t.left(1)
    t.circle(-150,47)
    t.end_fill()
    
    #ears
    t.penup()
    t.goto(110,-26)
    t.pendown()
    t.begin_fill()
    t.left(71)
    t.forward(10)
    t.right(10)
    t.forward(20)
    t.right(25)
    t.forward(5)
    t.right(22)
    t.circle(-24,180)
    t.right(60)
    t.circle(50,40)
    t.end_fill()

    t.penup()
    t.goto(-128,-55)
    t.pendown()
    t.begin_fill()
    t.forward(10)
    t.right(15)
    t.circle(-20,90)
    t.left(20)
    t.circle(-30,60)
    t.right(60)
    t.circle(-100,21)
    t.right(90)
    t.circle(60,40)
    t.end_fill()
    
    #beard
    t.penup()
    t.goto(138,-66)
    t.pendown()
    t.fillcolor("black")
    t.begin_fill()
    t.right(53)
    t.forward(15)
    t.right(15)
    t.forward(10)
    t.left(25)
    t.forward(25)
    t.left(185)
    t.circle(-40,60)
    t.left(30)
    t.forward(10)
    t.left(100)
    t.forward(17)
    t.end_fill()

    
    t.penup()
    t.goto(144,-120)
    t.pendown()
    t.begin_fill()
    t.left(125)
    t.circle(-40,60)
    t.left(155)
    t.circle(40,74)
    t.left(90)
    t.forward(17)
    t.end_fill()

    t.penup()
    t.goto(135,-170)
    t.pendown()
    t.begin_fill()
    t.left(40)
    t.circle(30,30)
    t.right(10)
    t.circle(-40,33)
    t.left(140)
    t.circle(25,80)
    t.left(25)
    t.forward(17)
    t.end_fill()

    t.penup()
    t.goto(-129,-63)
    t.pendown()
    t.begin_fill()
    t.right(30)
    t.forward(10)
    t.left(30)
    t.circle(-20,96)
    t.right(145)
    t.circle(30,65)
    t.right(60)
    t.forward(10)
    t.right(90)
    t.forward(10)
    t.end_fill()
    
    t.penup()
    t.goto(-138,-94)
    t.pendown()
    t.begin_fill()
    t.right(105)
    t.circle(15,80)
    t.right(77)
    t.forward(14)
    t.circle(-5,180)
    t.forward(5)
    t.circle(5,75)
    t.right(45)
    t.circle(-100,15)
    t.right(118)
    t.forward(10)
    t.end_fill()
    
    t.penup()
    t.goto(-144,-144)
    t.pendown()
    t.begin_fill()
    t.right(55)
    t.circle(40,50)
    t.right(150)
    t.circle(-40,51)
    t.right(80)
    t.forward(20)
    t.end_fill()
    
    #spot
    t.penup()
    t.goto(140,-2)
    t.pendown()
    t.begin_fill()
    t.left(80)
    t.circle(7,270)
    t.end_fill()

    t.penup()
    t.goto(154,-33)
    t.pendown()
    t.begin_fill()
    t.circle(5,270)
    t.end_fill()

    t.penup()
    t.goto(120,-33)
    t.pendown()
    t.fillcolor("#8B4513")
    t.begin_fill()
    t.left(36)
    t.forward(10)
    t.circle(-5,180)
    t.forward(10)
    t.end_fill()

    t.penup()
    t.goto(-137,-9)
    t.pendown()
    t.fillcolor("black")
    t.begin_fill()
    t.left(120)
    t.circle(-7,240)
    t.end_fill()

    t.penup()
    t.goto(-145,-40)
    t.pendown()
    t.begin_fill()
    t.right(45)
    t.circle(-7,270)
    t.end_fill()

    t.penup()
    t.goto(-120,-45)
    t.pendown()
    t.fillcolor("#8B4513")
    t.begin_fill()
    t.right(30)
    t.forward(10)
    t.circle(-5,180)
    t.forward(10)
    t.end_fill()

    #"wang"
    t.penup()
    t.goto(-40,-25)
    t.pendown()
    t.left(30)
    t.circle(100,45)
    t.penup()
    t.goto(-40,-40)
    t.pendown()
    t.right(25)
    t.forward(77)
    t.penup()
    t.goto(-40,-55)
    t.pendown()
    t.left(22)
    t.circle(-100,45)
    t.penup()
    t.goto(0,-31)
    t.pendown()
    t.right(68)
    t.forward(20)

    #face
    t.penup()
    t.goto(-104,-87)
    t.pendown()
    t.left(90)
    t.circle(-100,40)
    t.penup()
    t.goto(104,-67)
    t.pendown()
    t.right(130)
    t.circle(100,40)
    t.penup()
    t.goto(119,-147)
    t.pendown()
    t.right(40)
    t.circle(-200,35)
    t.penup()
    t.goto(0,-87)
    t.pendown()
    t.left(124)
    t.circle(-100,23)
    t.right(43)
    t.circle(-200,30)
    t.penup()
    t.goto(-30,-140)
    t.pendown()
    t.left(150)
    t.circle(60,60)
    t.penup()
    t.goto(-80,-100)
    t.fillcolor("black")
    t.pendown()
    t.begin_fill()
    t.circle(-10,360)
    t.end_fill()
    t.penup()
    t.goto(65,-90)
    t.pendown()
    t.begin_fill()
    t.circle(-10,360)
    t.end_fill()
    t.ht()

def snacks():
    t = RawTurtle(sc)
    #packet
    t.penup()
    t.goto(-215,-205)
    t.seth(31)
    t.pendown()
    t.pensize(4)
    t.pencolor("black")
    t.fillcolor(0,0.55,1)
    t.begin_fill()
    t.right(63)
    t.circle(90,65)
    t.left(80)
    t.circle(-100,38)
    t.left(94)
    t.circle(200,27)
    t.left(93)
    t.circle(-100,37)
    t.end_fill()
    t.penup()
    t.goto(-218,-144)
    t.pendown()
    t.fillcolor("white")
    t.begin_fill()
    t.right(150)
    t.forward(12)
    t.right(87)
    t.circle(-200,29)
    t.right(90)
    t.forward(11)
    t.right(90)
    t.circle(200,27)
    t.end_fill()

    #things
    t.penup()
    t.goto(-210,-130)
    t.pendown()
    t.fillcolor("yellow")
    t.begin_fill()
    t.right(130)
    t.circle(-30,110)
    t.end_fill()
    t.penup()
    t.goto(-167,-118)
    t.pendown()
    t.begin_fill()
    t.left(50)
    t.circle(-30,45)
    t.end_fill()
    t.penup()
    t.goto(-140,-125)
    t.pendown()
    t.begin_fill()
    t.left(120)
    t.circle(-9,180)
    t.end_fill()
    t.right(90)
    t.circle(200,27)

    #words :3 creators'name and number
    t.penup()
    t.goto(-208,-210)
    t.pendown()
    words="21XX1205\n缪善依\n2021WY1425\n陈昱衡\n2021WY1715\n王胡恺"
    t.write(words,font=('',10,'normal'))
    t.ht()

def juice():
    #bottle
    t = RawTurtle(sc)
    t.penup()
    t.goto(-140,-153)
    t.seth(195)
    t.pendown()
    t.fillcolor(0.85,0,0)
    t.begin_fill()
    t.right(178)
    t.circle(-100,29)
    t.right(83)
    t.forward(69)
    t.right(65)
    t.circle(-60,36)
    t.right(65)
    t.forward(69)
    t.end_fill()
    t.fillcolor("white")
    t.begin_fill()
    t.left(90)
    t.forward(2)
    t.right(90)
    t.forward(5)
    t.right(81)
    t.circle(-100,35)
    t.right(81)
    t.forward(5)
    t.right(97)
    t.circle(100,35)
    t.end_fill()

    #straw
    t.penup()
    t.goto(-103,-143)
    t.pendown()
    t.begin_fill()
    t.right(110)
    t.forward(30)
    t.circle(-10,60)
    t.forward(10)
    t.circle(-3,180)
    t.forward(10)
    t.circle(5,60)
    t.forward(30)
    t.right(90)
    t.forward(6)
    t.end_fill()
    t.ht()

def 头():
  t = RawTurtle(sc)
  t.pensize(4)
  t.fillcolor('#32BEFF')
  t.pu()
  t.goto(64.0, -48.0)
  t.pd()
  t.begin_fill()
  t.goto(54.0, -54.0)
  t.goto(43.0, -59.0)
  t.goto(33.0, -63.0)
  t.goto(15.0, -67.0)
  t.goto(2.0, -71.0)
  t.goto(-12.0, -76.0)
  t.goto(-27.0, -76.0)
  t.goto(-47.0, -78.0)
  t.goto(-59.0, -75.0)
  t.goto(-74.0, -71.0)
  t.goto(-86.0, -64.0)
  t.goto(-94.0, -57.0)
  t.goto(-100.0, -45.0)
  t.goto(-103.0, -36.0)
  t.goto(-107.0, -25.0)
  t.goto(-110.0, -15.0)
  t.goto(-112.0, -5.0)
  t.goto(-113.0, 8.0)
  t.goto(-113.0, 23.0)
  t.goto(-111.0, 39.0)
  t.goto(-108.0, 50.0)
  t.goto(-106.0, 61.0)
  t.goto(-99.0, 78.0)
  t.goto(-92.0, 89.0)
  t.goto(-85.0, 98.0)
  t.goto(-83.0, 103.0)
  t.goto(-74.0, 111.0)
  t.goto(-66.0, 122.0)
  t.goto(-58.0, 133.0)
  t.goto(-52.0, 142.0)
  t.goto(-46.0, 150.0)
  t.goto(-38.0, 155.0)
  t.goto(-31.0, 156.0)
  t.goto(-25.0, 156.0)
  t.goto(-19.0, 154.0)
  t.goto(-16.0, 149.0)
  t.goto(-14.0, 141.0)
  t.goto(-16.0, 134.0)
  t.goto(-21.0, 128.0)
  t.goto(-24.0, 123.0)
  t.goto(-26.0, 117.0)
  t.goto(-25.0, 112.0)
  t.goto(-20.0, 109.0)
  t.goto(-16.0, 109.0)
  t.goto(-12.0, 111.0)
  t.goto(-8.0, 115.0)
  t.goto(-7.0, 121.0)
  t.goto(-5.0, 126.0)
  t.goto(0.0, 131.0)
  t.goto(6.0, 138.0)
  t.goto(13.0, 140.0)
  t.goto(20.0, 140.0)
  t.goto(25.0, 138.0)
  t.goto(28.0, 134.0)
  t.goto(29.0, 126.0)
  t.goto(27.0, 120.0)
  t.goto(24.0, 113.0)
  t.goto(23.0, 108.0)
  t.goto(24.0, 103.0)
  t.goto(28.0, 103.0)
  t.goto(31.0, 106.0)
  t.goto(34.0, 112.0)
  t.goto(36.0, 117.0)
  t.goto(40.0, 124.0)
  t.goto(48.0, 127.0)
  t.goto(52.0, 127.0)
  t.goto(58.0, 127.0)
  t.goto(64.0, 124.0)
  t.goto(68.0, 119.0)
  t.goto(69.0, 111.0)
  t.goto(68.0, 104.0)
  t.goto(68.0, 98.0)
  t.goto(73.0, 91.0)
  t.goto(77.0, 85.0)
  t.goto(81.0, 78.0)
  t.goto(83.0, 71.0)
  t.goto(85.0, 64.0)
  t.goto(86.0, 59.0)
  t.goto(91.0, 62.0)
  t.goto(98.0, 61.0)
  t.goto(104.0, 53.0)
  t.goto(107.0, 47.0)
  t.goto(109.0, 40.0)
  t.goto(109.0, 34.0)
  t.goto(108.0, 26.0)
  t.goto(106.0, 19.0)
  t.goto(103.0, 13.0)
  t.goto(101.0, 8.0)
  t.goto(97.0, 3.0)
  t.goto(96.0, -0.0)
  t.goto(96.0, -5.0)
  t.goto(96.0, -9.0)
  t.goto(93.0, -12.0)
  t.goto(87.0, -19.0)
  t.goto(85.0, -20.0)
  t.goto(84.0, -25.0)
  t.goto(81.0, -28.0)
  t.goto(78.0, -34.0)
  t.goto(73.0, -39.0)
  t.goto(70.0, -43.0)
  t.goto(64.0, -45.0)
  t.goto(64.0, -45.0)
  t.end_fill()
  t.ht()

def 脸():
  t = RawTurtle(sc)
  t.pensize(4)
  t.fillcolor('#FDC4BB')
  t.pu()
  t.goto(37.0, -61.0)
  t.pd()
  t.begin_fill()
  t.goto(27.0, -65.0)
  t.goto(16.0, -68.0)
  t.goto(6.0, -71.0)
  t.goto(-3.0, -73.0)
  t.goto(-14.0, -76.0)
  t.goto(-23.0, -77.0)
  t.goto(-33.0, -78.0)
  t.goto(-40.0, -78.0)
  t.goto(-47.0, -77.0)
  t.goto(-57.0, -75.0)
  t.goto(-66.0, -73.0)
  t.goto(-74.0, -69.0)
  t.goto(-79.0, -62.0)
  t.goto(-84.0, -57.0)
  t.goto(-87.0, -48.0)
  t.goto(-89.0, -42.0)
  t.goto(-91.0, -33.0)
  t.goto(-91.0, -24.0)
  t.goto(-93.0, -16.0)
  t.goto(-94.0, -12.0)
  t.goto(-94.0, -8.0)
  t.goto(-88.0, -6.0)
  t.goto(-81.0, -5.0)
  t.goto(-75.0, -6.0)
  t.goto(-68.0, -8.0)
  t.goto(-56.0, -9.0)
  t.goto(-50.0, -10.0)
  t.goto(-44.0, -10.0)
  t.goto(-37.0, -10.0)
  t.goto(-30.0, -9.0)
  t.goto(-22.0, -6.0)
  t.goto(-15.0, -3.0)
  t.goto(-7.0, 2.0)
  t.goto(3.0, 7.0)
  t.goto(7.0, 13.0)
  t.goto(11.0, 15.0)
  t.goto(15.0, 18.0)
  t.goto(23.0, 17.0)
  t.goto(28.0, 17.0)
  t.goto(33.0, 17.0)
  t.goto(39.0, 16.0)
  t.goto(42.0, 16.0)
  t.goto(48.0, 14.0)
  t.goto(52.0, 9.0)
  t.goto(55.0, 1.0)
  t.goto(57.0, -5.0)
  t.goto(59.0, -12.0)
  t.goto(60.0, -22.0)
  t.goto(60.0, -30.0)
  t.goto(57.0, -37.0)
  t.goto(54.0, -43.0)
  t.goto(49.0, -51.0)
  t.goto(42.0, -56.0)
  t.end_fill()
  t.fillcolor('#147BED')
  t.pensize(2)
  t.pu()
  t.goto(-77.0, -3.0)
  t.pd()
  t.begin_fill()
  t.goto(-69.0, -6.0)
  t.goto(-63.0, -8.0)
  t.goto(-54.0, -9.0)
  t.goto(-46.0, -10.0)
  t.goto(-40.0, -10.0)
  t.goto(-33.0, -9.0)
  t.goto(-24.0, -7.0)
  t.goto(-16.0, -4.0)
  t.goto(-9.0, -1.0)
  t.goto(-2.0, 3.0)
  t.goto(4.0, 8.0)
  t.goto(10.0, 13.0)
  t.goto(15.0, 18.0)
  t.goto(2.0, 17.0)
  t.goto(-4.0, 17.0)
  t.goto(-11.0, 19.0)
  t.goto(-19.0, 20.0)
  t.goto(-25.0, 21.0)
  t.goto(-32.0, 22.0)
  t.goto(-39.0, 22.0)
  t.goto(-45.0, 22.0)
  t.goto(-49.0, 20.0)
  t.goto(-55.0, 16.0)
  t.goto(-62.0, 11.0)
  t.goto(-68.0, 7.0)
  t.goto(-71.0, 3.0)
  t.goto(-76.0, -1.0)
  t.end_fill()
  t.goto(-55, 1)
  t.setheading(100)
  t.fillcolor('#2DDECC')
  t.begin_fill()
  t.circle(-5, 360)
  t.end_fill()
  t.pu()
  t.circle(-5, 170)
  t.pd()
  t.begin_fill()
  t.circle(8, 360)
  t.end_fill()
  t.pu()
  t.circle(8, 170)
  t.pd()
  t.begin_fill()
  t.circle(-5, 360)
  t.end_fill()
  t.pu()
  t.goto(-74.59, -4.31)
  t.pd()
  t.setheading(10)
  t.goto(13.58, 18.42)
  t.pu()
  t.goto(-92.29, -7.5)
  t.pd()
  t.setheading(110)
  t.fd(12)
  t.circle(3, 60)
  t.fd(10)
  t.rt(10)
  t.fd(5)
  t.pu()
  t.goto(-74.59, -4.31)
  t.setheading(10)
  t.bk(8)
  t.setheading(55)
  t.pd()
  t.pensize(2)
  t.fd(40)
  t.circle(-32, 80)
  t.rt(10)
  t.fd(10)
  t.lt(10)
  t.fd(10)
  t.goto(13.58, 18.42)
  t.pu()
  t.setheading(-5)
  t.fd(25)
  t.lt(90)
  t.pd()
  t.circle(-20, 60)
  t.circle(3, 50)
  t.fd(17)
  t.circle(-20, 80)
  t.fd(10)
  t.pu()
  t.goto(87.31, 62.17)
  t.setheading(285)
  t.pensize(3)
  t.pd()
  t.rt(45)
  t.fd(22)
  t.lt(40)
  t.fd(20)
  t.rt(10)
  t.fd(40)
  t.lt(105)
  t.fd(5)
  t.pu()
  t.bk(5)
  t.lt(-105)
  t.bk(5)
  t.fillcolor('#1280F9')
  t.begin_fill()
  t.pd()
  t.lt(90)
  t.fd(3)
  t.lt(60)
  t.fd(10)
  t.lt(10)
  t.fd(10)
  t.lt(20)
  t.fd(10)
  t.rt(30)
  t.fd(15)
  t.lt(10)
  t.fd(15)
  t.circle(5, 150)
  t.fd(10)
  t.lt(10)
  t.fd(15)
  t.end_fill()
  t.pu()
  t.lt(45)
  t.fd(10)
  t.pd()
  t.lt(120)
  t.fd(20)
  t.pu()
  t.bk(20)
  t.lt(-120)
  t.fd(10)
  t.lt(120)
  t.pd()
  t.fd(15)
  t.pu()
  t.bk(15)
  t.lt(-120)
  t.fd(10)
  t.lt(80)
  t.pd()
  t.fd(8)
  t.pu()
  t.goto(0, -45)
  t.setheading(218)
  # print(t.heading())
  t.pensize(2)
  t.fillcolor('#F92C34')
  # t.stamp()
  t.pd()
  t.fd(10)
  t.begin_fill()
  t.rt(5)
  t.fd(10)
  t.rt(30)
  t.fd(5)
  t.circle(-6, 180)
  t.rt(30)
  t.fd(10)
  t.end_fill()
  t.pu()  
  t.ht()

def 身子():
  t = RawTurtle(sc)
  t.pensize(2)
  t.fillcolor('#BC0010')
  t.pu()
  t.goto(65.0, -47.0)
  t.pd()
  t.begin_fill()
  t.goto(65.0, -52.0)
  t.goto(67.0, -54.0)
  t.goto(71.0, -56.0)
  t.goto(73.0, -59.0)
  t.goto(73.0, -63.0)
  t.goto(72.0, -66.0)
  t.goto(75.0, -70.0)
  t.goto(77.0, -75.0)
  t.goto(79.0, -80.0)
  t.goto(81.0, -85.0)
  t.goto(86.0, -98.0)
  t.goto(90.0, -108.0)
  t.goto(90.0, -118.0)
  t.goto(86.0, -127.0)
  t.goto(84.0, -129.0)
  t.goto(77.0, -134.0)
  t.goto(71.0, -137.0)
  t.goto(66.0, -139.0)
  t.goto(59.0, -142.0)
  t.goto(53.0, -144.0)
  t.goto(49.0, -144.0)
  t.goto(44.0, -141.0)
  t.goto(41.0, -140.0)
  t.goto(39.0, -143.0)
  t.goto(39.0, -147.0)
  t.goto(31.0, -151.0)
  t.goto(23.0, -153.0)
  t.goto(19.0, -154.0)
  t.goto(11.0, -154.0)
  t.goto(2.0, -155.0)
  t.goto(-7.0, -154.0)
  t.goto(-12.0, -154.0)
  t.goto(-19.0, -152.0)
  t.goto(-28.0, -151.0)
  t.goto(-34.0, -148.0)
  t.goto(-36.0, -146.0)
  t.goto(-41.0, -143.0)
  t.goto(-45.0, -139.0)
  t.goto(-50.0, -138.0)
  t.goto(-54.0, -137.0)
  t.goto(-60.0, -140.0)
  t.goto(-64.0, -140.0)
  t.goto(-70.0, -136.0)
  t.goto(-74.0, -133.0)
  t.goto(-79.0, -127.0)
  t.goto(-80.0, -121.0)
  t.goto(-81.0, -115.0)
  t.goto(-81.0, -109.0)
  t.goto(-80.0, -103.0)
  t.goto(-76.0, -97.0)
  t.goto(-73.0, -93.0)
  t.goto(-66.0, -86.0)
  t.goto(-61.0, -81.0)
  t.goto(-57.0, -77.0)
  t.goto(-54.0, -74.0)
  t.end_fill()
  t.ht()

def 腿():
  t = RawTurtle(sc)
  t.pensize(2)
  t.fillcolor('#573528')
  t.pu()
  t.goto(81.0, -132.0)
  t.pd()
  t.begin_fill()
  t.goto(84.0, -139.0)
  t.goto(89.0, -149.0)
  t.goto(91.0, -159.0)
  t.goto(91.0, -159.0)
  t.goto(91.0, -168.0)
  t.goto(89.0, -176.0)
  t.goto(86.0, -184.0)
  t.goto(77.0, -191.0)
  t.goto(71.0, -196.0)
  t.goto(64.0, -201.0)
  t.goto(50.0, -202.0)
  t.goto(44.0, -202.0)
  t.goto(35.0, -204.0)
  t.goto(31.0, -211.0)
  t.goto(26.0, -213.0)
  t.goto(21.0, -209.0)
  t.goto(18.0, -205.0)
  t.goto(16.0, -200.0)
  t.goto(12.0, -193.0)
  t.goto(10.0, -188.0)
  t.goto(6.0, -189.0)
  t.goto(5.0, -195.0)
  t.goto(3.0, -200.0)
  t.goto(-2.0, -206.0)
  t.goto(-6.0, -209.0)
  t.goto(-10.0, -211.0)
  t.goto(-17.0, -207.0)
  t.goto(-18.0, -202.0)
  t.goto(-15.0, -197.0)
  t.goto(-15.0, -195.0)
  t.goto(-20.0, -195.0)
  t.goto(-27.0, -197.0)
  t.goto(-33.0, -197.0)
  t.goto(-45.0, -201.0)
  t.goto(-55.0, -201.0)
  t.goto(-68.0, -198.0)
  t.goto(-79.0, -193.0)
  t.goto(-86.0, -187.0)
  t.goto(-91.0, -179.0)
  t.goto(-91.0, -175.0)
  t.goto(-91.0, -164.0)
  t.goto(-87.0, -155.0)
  t.goto(-82.0, -145.0)
  t.goto(-79.0, -141.0)
  t.goto(-72.0, -134.0)
  t.end_fill()
  t.ht()

def 眼睛():
  t = RawTurtle(sc)
  t.pu()
  t.goto(-60, -50)
  t.seth(268)
  t.rt(90)
  t.fd(-13)
  t.fillcolor('#031276')
  t.pensize(4)
  t.lt(90)
  t.fd(-5)
  t.pd()
  t.begin_fill()
  t.circle(-10, 170)
  t.fd(17)
  t.circle(-10, 180)
  t.goto(-46.83, -45.46)
  t.end_fill()
  t.pu()
  t.rt(90)
  t.fd(10)
  t.rt(90)
  t.fd(3)
  t.pd()
  t.pencolor('#FFFFFF')
  t.circle(2, 360)
  t.pu()
  t.fd(13)
  t.pd()
  t.circle(-2, 360)
  t.pu()
  
  t.goto(27, -10)
  t.pensize(5)
  t.pencolor('black')
  t.seth(218)
  t.pd()
  t.fd(10)
  t.rt(5)
  t.fd(12)
  t.lt(150)
  t.fd(20)
  t.pu()
  t.ht()

def 手():
  t = RawTurtle(sc)
  t.pensize(2)
  t.pu()
  t.goto(34, -110)
  t.setheading(170)
  t.pd()
  t.fillcolor('#32BEFF')
  t.begin_fill()
  t.fd(5)
  t.circle(5, 90)
  t.fd(5)
  t.lt(30)
  t.fd(10)
  t.lt(15)
  t.fd(10)
  t.goto(42, -140)
  t.end_fill()
  t.goto(34, -110)
  t.setheading(90)
  t.fd(3)
  t.rt(90)
  t.fd(5)
  t.lt(90)
  t.fd(5)
  t.rt(90)
  t.circle(22, 90)
  t.pu()

  t.goto(-29, -112)
  t.setheading(-15)
  t.pd()
  t.begin_fill()
  t.fd(10)
  t.circle(-5, 90)
  t.rt(20)
  t.fd(15)
  t.circle(-10, 40)
  t.goto(-43, -137)
  t.end_fill()
  t.goto(-29, -112)
  t.setheading(45)
  t.circle(10, 90)
  t.fd(10)
  t.lt(45)
  t.fd(15)
  t.pu()
  t.bk(10)
  t.rt(90)
  t.pd()
  t.fd(6)
  t.pu()
  t.ht()

def 衣服():
  t = RawTurtle(sc)
  t.pensize(2)
  t.pu()
  t.goto(70.0, -63.0)
  t.pd()
  t.goto(61.0, -65.0)
  t.goto(52.0, -66.0)
  t.goto(45.0, -67.0)
  t.goto(36.0, -70.0)
  t.goto(26.0, -72.0)
  t.goto(21.0, -75.0)
  t.goto(12.0, -77.0)
  t.goto(5.0, -80.0)
  t.goto(-1.0, -81.0)
  t.goto(-3.0, -82.0)
  t.goto(-12.0, -82.0)
  t.goto(-17.0, -81.0)
  t.goto(-24.0, -79.0)
  t.goto(-29.0, -78.0)
  t.goto(-18.0, -75.0)
  t.goto(-10.0, -74.0)
  t.goto(-7.0, -74.0)
  t.goto(-3.0, -80.0)
  t.goto(5.0, -70.0)
  t.ht()

def 裤子():
  t = RawTurtle(sc)
  t.pensize(2)
  t.penup()
  t.goto(35.0, -205.0)
  t.pd()
  t.goto(30.0, -200.0)
  t.goto(28.0, -192.0)
  t.goto(25.0, -182.0)
  t.goto(25.0, -175.0)
  t.goto(24.0, -167.0)
  t.goto(23.0, -164.0)
  t.goto(28.0, -164.0)
  t.goto(34.0, -156.0)
  t.goto(39.0, -151.0)
  t.goto(44.0, -148.0)
  t.goto(48.0, -143.0)
  t.goto(44.0, -141.0)
  t.goto(37.0, -148.0)
  t.pu()
  t.goto(-49.0, -139.0)
  t.pd()
  t.goto(-46.0, -145.0)
  t.goto(-40.0, -150.0)
  t.goto(-38.0, -153.0)
  t.goto(-30.0, -153.0)
  t.goto(-23.0, -155.0)
  t.goto(-17.0, -158.0)
  t.goto(-14.0, -163.0)
  t.goto(-10.0, -165.0)
  t.goto(-11.0, -173.0)
  t.goto(-14.0, -182.0)
  t.goto(-14.0, -192.0)
  t.goto(-17.0, -195.0)
  t.pu()
  t.goto(-42.0, -150.0)
  t.pd()
  t.goto(-50.0, -151.0)
  t.goto(-55.0, -151.0)
  t.goto(-63.0, -148.0)
  t.ht()

def 袜子():
  t = RawTurtle(sc)
  t.pensize(2)
  t.fillcolor('#D87F75')
  t.pu()
  t.goto(7.0, -184.0)
  t.pd()
  t.begin_fill()
  t.goto(6.0, -188.0)
  t.goto(5.0, -194.0)
  t.goto(2.0, -201.0)
  t.goto(-2.0, -207.0)
  t.goto(-7.0, -211.0)
  t.goto(-14.0, -211.0)
  t.goto(-18.0, -206.0)
  t.goto(-18.0, -201.0)
  t.goto(-15.0, -195.0)
  t.goto(-14.0, -186.0)
  t.goto(-14.0, -178.0)
  t.goto(-11.0, -172.0)
  t.goto(-8.0, -166.0)
  t.goto(-1.0, -167.0)
  t.goto(5.0, -171.0)
  t.goto(6.0, -175.0)
  t.goto(10.0, -182.0)
  t.goto(11.0, -189.0)
  t.goto(14.0, -196.0)
  t.goto(16.0, -202.0)
  t.goto(21.0, -209.0)
  t.goto(25.0, -213.0)
  t.goto(29.0, -213.0)
  t.goto(34.0, -208.0)
  t.goto(34.0, -204.0)
  t.goto(29.0, -200.0)
  t.goto(26.0, -191.0)
  t.goto(25.0, -183.0)
  t.goto(25.0, -178.0)
  t.goto(23.0, -169.0)
  t.goto(22.0, -166.0)
  t.goto(15.0, -170.0)
  t.goto(11.0, -175.0)
  t.goto(9.0, -181.0)
  t.end_fill()
  t.ht()

def 手机():
  t = RawTurtle(sc)
  t.pensize(2)
  t.fillcolor('#27201E')
  t.pu()
  t.goto(-28.0, -104.0)
  t.pd()
  t.begin_fill()
  t.goto(-25.0, -137.0)
  t.goto(2.0, -136.0)
  t.goto(28.0, -134.0)
  t.goto(34.0, -109.0)
  t.goto(32.0, -99.0)
  t.goto(3.0, -101.0)
  t.goto(-27.0, -103.0)
  t.end_fill()
  t.ht()
  t.pencolor('#B1AEAE')
  t.pu()
  t.goto(-21.0, -108.0)
  t.pd()
  t.circle(1, 360)
  t.pu()
  t.goto(-14.0, -107.0)
  t.pd()
  t.circle(1, 360)

def 怎么还少画了耳朵():
  t = RawTurtle(sc)
  t.pensize(4)
  t.fillcolor('#32BEFF')
  t.pu()
  t.goto(-100.0, -50.0)
  t.pd()
  t.begin_fill()
  t.goto(-107.0, -47.0)
  t.goto(-112.0, -40.0)
  t.goto(-117.0, -33.0)
  t.goto(-121.0, -25.0)
  t.goto(-124.0, -16.0)
  t.goto(-127.0, -7.0)
  t.goto(-129.0, -0.0)
  t.goto(-129.0, 7.0)
  t.goto(-128.0, 11.0)
  t.goto(-123.0, 15.0)
  t.goto(-119.0, 16.0)
  t.goto(-114.0, 16.0)
  t.goto(-114.0, 6.0)
  t.goto(-113.0, -6.0)
  t.goto(-110.0, -14.0)
  t.goto(-107.0, -22.0)
  t.goto(-104.0, -34.0)
  t.goto(-100.0, -45.0)
  t.goto(-97.0, -50.0)
  t.end_fill()
  t.pu()
  t.goto(-113.0, -0.0)
  t.pd()
  t.fillcolor('#1480FA')
  t.pensize(2)
  t.begin_fill()
  t.goto(-119.0, 3.0)
  t.goto(-122.0, -2.0)
  t.goto(-121.0, -11.0)
  t.goto(-119.0, -17.0)
  t.goto(-117.0, -24.0)
  t.goto(-112.0, -30.0)
  t.goto(-108.0, -38.0)
  t.goto(-102.0, -41.0)
  t.end_fill()
  t.pu()
  t.goto(-109.0, -35.0)
  t.pd()
  t.goto(-104.0, -33.0)
  t.pu()
  t.goto(-108.0, -24.0)
  t.pd()
  t.goto(-115.0, -25.0)
  t.pu()
  t.goto(-121.0, -8.0)
  t.pd()
  t.goto(-112.0, -11.0)
  t.ht()

root = TK.Tk()
cv = TK.Canvas(root, width=500, height=500)
cv.pack()
sc = TurtleScreen(cv)
sc.bgcolor('#A00B1A')
tiger()
snacks()
juice()
腿()
身子()
手机()
手()
怎么还少画了耳朵()
头()
脸()
眼睛()
衣服()
裤子()
袜子()

TK.mainloop()

