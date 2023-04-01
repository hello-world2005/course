import os
from flask import Flask, render_template, request, redirect, session, flash
import sqlite3
from datetime import timedelta
from function import *
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, EqualTo
from flask_bootstrap import Bootstrap5
import hashlib

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
  submit = SubmitField(label = u'登陆')

@app.route('/', methods = ['GET'])
def Index():
  if ('username' in session):
    username = session['username']
  else:
    username = None
  if (username == None):
    redirect('/login')
  data = FetchData()
  return render_template('index.html')

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

if __name__ == '__main__':
  app.run()
