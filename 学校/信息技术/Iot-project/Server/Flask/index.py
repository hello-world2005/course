import os
from flask import Flask, render_template, request, redirect, session, flash, jsonify
import sqlite3
from datetime import timedelta
from function import *
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, EqualTo
from flask_bootstrap import Bootstrap5
import hashlib
import time

app = Flask(__name__)
app.config['SESSION_KEY'] = os.urandom(8)
app.config['PERMANENT_SESSION_LIFETIME'] = timedelta(days = 7)
app.config['SECRET_KEY'] = os.urandom(8)
bootstrap = Bootstrap5(app)
# CsrfProtect(app)
md5 = hashlib.md5()

class RegisterForm(FlaskForm):
  username = StringField(label = u'用户名', validators = [DataRequired(u'用户名非空')])
  password = PasswordField(label = u'密码', validators = [DataRequired(u'密码非空')])
  repassword = PasswordField(label = u'重复密码', validators = [EqualTo('password', u'密码不一致')])
  submit = SubmitField(label = u'注册')

class LoginForm(FlaskForm):
  username = StringField(label = u'用户名', validators = [DataRequired(u'用户名非空')])
  password = PasswordField(label = u'密码', validators = [DataRequired(u'密码非空')])
  submit = SubmitField(label = u'登录')

@app.route('/', methods = ['GET'])
def Index():
  if ('username' in session):
    username = session['username']
  else:
    username = None
  if (username == None):
    redirect('/login')
  data = FetchData()
  if ('username' not in session):
    return render_template('index_nologin.html')
  else:
    return render_template('index.html', name = session['username'])

@app.route('/login', methods = ['GET', 'POST'])
def Login():
  form = LoginForm()
  if (form.validate_on_submit()):
    username = form.username.data
    md5.update(form.password.data.encode('utf-8'))
    password = md5.hexdigest()
    db = sqlite3.connect('data/data.sqlite')
    cur = db.cursor()
    cur.execute('select * from user where username = "%s"' % username)
    res = cur.fetchall()
    cur.close()
    db.close()
    print(res)
    if (len(res) > 0):
      password1 = res[0][2]
      if (password == password1):
        session['username'] = username
        flash('登录成功', 'success')
        return redirect('/')
    else:
      flash(u'用户名或密码错误', 'danger')
  return render_template('login.html', form = form)

@app.route('/regist', methods = ['GET', 'POST'])
def Regist():
  form = RegisterForm()
  if (form.validate_on_submit()):
    username = form.username.data
    md5.update(form.password.data.encode('utf-8'))
    password = md5.hexdigest()
    db = sqlite3.connect('data/data.sqlite')
    cur = db.cursor()
    cur.execute('insert into user (username, password, level) values ("%s", "%s", 1)' % (username, password))
    db.commit()
    cur.close()
    db.close()
    flash(u'注册成功', 'success')
    return redirect('/login')
  else:
    flash(u'用户名或密码不合法')
  return render_template('regist.html', form = form)

@app.route('/logout')
def Logout():
  if ('username' in session):
    del session['username']
  return redirect('/login')

@app.route('/input')
def Input():
  id = request.args.get('id')
  data = request.args.get('rawdata')
  t = time.localtime()
  ti = time.strftime('%Y-%m-%d %H:%M:%S', t)
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  cur.execute('insert into data (sensorid, val, timestamp) values ("%s", "%s", "%s")' % (id, data, ti))
  db.commit()
  cur.close()
  db.close()
  return 'ok'

@app.route('/amp')
def Amp():
  return app.send_static_file('data.amp')

@app.route('/fetchdata')
def FetchData():
  filt = request.args.get('filter')
  if (filt == None): return jsonify({})
  print('Fetch', filt)
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  cur.execute('select * from sensor where cata="%s"' % filt)
  sensor = cur.fetchall()
  data = []
  res = {}
  print(sensor)
  for i in sensor:
    id, place = i[0], i[2]
    cur.execute('select * from data where sensorid="%s"' % id)
    d = cur.fetchall()
    if (len(d) > 10):
      d = d[-10:]
    _ = {}
    _['name'] = place
    _['data'] = []
    for j in d:
      _['data'].append(j[2])
    data.append(_)
  res['data'] = data
  i = sensor[0]
  cur.execute('select * from data where sensorid="%s"' % i[0])
  d = cur.fetchall()
  if (len(d) > 10):
    d = d[-10:]
  _ = []
  for j in d:
    _.append(j[3][5:-6])
  res['time'] = _
  cur.close()
  db.close()
  return jsonify(res)
  # return jsonify(_data)

@app.route('/guest')
def Guest():
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  cur.execute('select * from guest')
  guest = cur.fetchall()
  if (len(guest) > 5):
    guest = guest[-5:]
  data = {}
  x = 0
  for i in guest:
    x += 1
    data[x] = {'name': i[1], 'time': i[2]}
  cur.close()
  db.close()
  return jsonify(data)

@app.route('/newguest')
def NewGuest():
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  name = request.args.get('name')
  t = time.localtime()
  ti = time.strftime('%Y-%m-%d %H:%M:%S', t)
  cur.execute('insert into guest (name, timestamp) values ("%s", "%s")' % (name, ti))
  db.commit()
  cur.close()
  db.close()
  return 'success'

@app.route('/control')
def Control():
  if ('username' not in session):
    return redirect('/login')
  return render_template('control.html', name = session['username'])

@app.route('/windows')
def Windows():
  data = []
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  cur.execute('select * from windows')
  _data = cur.fetchall()
  qwq = {}
  x = 0
  for i in _data:
    qwq[i[1]] = i[2]
  for i in qwq:
    data.append({'place': i, 'status': qwq[i]})
  cur.close()
  db.close()
  print(data)
  return jsonify(data)

@app.route('/setwindow', methods = ['GET', 'POST'])
def SetWindow():
  if (request.method == 'GET'): return 'qwq'
  name = request.form.get('name')
  stat = request.form.get('stat')
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  cur.execute('insert into windows (name, stat) values ("%s", %d)' % (name, int(stat)))
  db.commit()
  cur.close()
  db.close()
  return 'success'

@app.route('/cron')
def Cron():
  id = request.args.get('id')
  t = time.localtime()
  ti = time.strftime('%Y-%m-%d %H:%M:%S', t)
  db = sqlite3.connect('data/data.sqlite')
  cur = db.cursor()
  cur.execute('select cata from sensor where id=%s' % id)
  data = cur.fetchall()
  if (len(data) == 1):
    cata = data[0]
    if (cata == 'therometer' or cata == 'humidity'):
      if (ti[-5:] == '01:00'): 
        cur.close(); db.close()
        return 'd'
    else:
      cur.close(); db.close()
      return 'n'
  cur.execute('select place from servo where id="%s"' % id)
  data = cur.fetchall()
  if (len(data) == 1):
    pla = data[0]
    cur.execute('select stat from windows where name="%s"' % pla)
    data = cur.fetchall()
    sta = data[-1]
    if (sta == 0): 
      cur.close(); db.close()
      return 'O'
    else: 
      cur.close(); db.close()
      return 'C'
  cur.close(); db.close()
  return ''

if __name__ == '__main__':
  app.run(debug=True)
