import sqlite3
import os
import random
import time

p = os.getcwd()
print(p)
db = sqlite3.connect('data/data.sqlite')
cur = db.cursor()
# ID INT PRIMARY KEY
# cur.execute('create table user(id integer primary key autoincrement, username text, password text, level int)')
# cur.execute('create table sensor(id int, cata text)')
# cur.execute('create table data(sensorid int, val text, timestamp datetime)')
# cur.execute('insert into sensor (id, cata) values (2, "humidity")')
# cur.execute('drop table guest')
# cur.execute('create table guest(id integer primary key autoincrement, name text, timestamp datetime)')
# cur.execute('create table windows(id integer primary key autoincrement, name text, stat bool)')
# for i in range(20):
#   t = time.localtime()
#   ti = time.strftime('%Y-%m-%d %H:%M:%S', t)
#   cur.execute('insert into data (sensorid, val, timestamp) values (2, "%d", "%s")' % (random.randint(20, 100), ti))
#   time.sleep(1)
#   db.commit()
# t = time.localtime()
# ti = time.strftime('%Y-%m-%d %H:%M:%S', t)
cur.execute('insert into windows (name, stat) values ("%s", False)' % ('b1'))
db.commit()
