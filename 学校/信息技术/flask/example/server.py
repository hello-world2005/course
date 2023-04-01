from flask import Flask, render_template, request, flash, Markup, redirect
from flask_bootstrap import Bootstrap5
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, validators, ValidationError

app = Flask(__name__)
bootstrap = Bootstrap5(app)
app.config['SECRET_KEY'] = 'Fuck'

class User(FlaskForm):
  username = StringField(validators = [validators.DataRequired(), validators.Length(4, 10)])
  password = PasswordField(validators = [validators.DataRequired(), validators.Length(6, 18)])
  submit = SubmitField()

class UserRe(FlaskForm):
  username = StringField(validators = [validators.DataRequired(), validators.Length(4, 10)])
  password = PasswordField(validators = [validators.DataRequired(), validators.Length(6, 18)])
  repassword = PasswordField(validators = [validators.DataRequired(), validators.Length(6, 18)])
  submit = SubmitField()

  def validate_repassword(self, field):
    if (field.data != self.password.data):
      raise ValidationError('密码不符')

username, password = '', ''
pas = {'qwqwq':'123456'}

@app.route('/', methods = ['GET'])
def index():
  return 'qwq'

@app.route('/regist', methods = ['GET', 'POST'])
def Regist():
  user = UserRe()
  if (user.validate_on_submit()):
    if (user.validate()):
      usern = user.username.data
      passw = user.password.data
      if (usern in pas):
        flash('用户名已存在', 'danger')
      else:
        pas[usern] = passw
        flash('注册成功，请登录……', 'success')
        return redirect('/login')
    else:
      flash('密码不符', 'danger')
  return render_template('regist.html', form = user)

@app.route('/login', methods = ['GET', 'POST'])
def Login():
  global username, password
  user = User()
  if (user.validate_on_submit()):
    username = user.username.data
    print(username, password)
    if (username in pas and pas[username] == user.password.data):
      flash('登录成功', 'success')
      return redirect('/')
    else:
      flash('用户名或密码错误', 'danger')
  return render_template('login.html', form = user)

if __name__ == '__main__':
  app.run()
