import sqlite3
import os

p = os.getcwd()
print(p)
db = sqlite3.connect('data/data.sqlite')
cur = db.cursor()
# ID INT PRIMARY KEY
cur.execute('create table user(id integer primary key autoincrement, username text, password text, level int)')
cur.execute('create table sensor(id int, cata text)')
cur.execute('create table data(sensorid int, val text, timestamp datetime)')
