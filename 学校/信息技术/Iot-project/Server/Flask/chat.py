# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from flask import Flask,render_template,request,redirect #导入Flask框架模块
import sqlite3
app = Flask(__name__)
a = []
#userinfo = {'admin':'123','SXT':'111','WMF':'222','WJH':'333','ZJK':'444'}
dic_online = {}

@app.route("/",methods=["GET","POST"])
def login():
    if request.method == 'POST':
        username = request.form.get('user')
        password = request.form.get('psd')

        db=sqlite3.connect('data/data.db')
        cur=db.cursor()
        #cur.execute("select username,password from userinfo where username='"+username+"'")
        cur.execute("select username,password from userinfo where username='%s'"%username)
        data=cur.fetchall()
        cur.close()
        db.close()
        #if username in userinfo:
        if len(data)>0:
            #if userinfo[username] == password:
            if data[0][1]==password:
                ip = request.remote_addr
                dic_online[ip] = username
                return redirect('/chat')
    return render_template('login.html')

@app.route("/reg",methods=["GET","POST"])
def register():
    if request.method == 'POST':
        username = request.form.get('user')
        password = request.form.get('psd')
        if username and len(username)>0:
            db=sqlite3.connect('data/data.db')
            cur=db.cursor()
            #cur.execute("select username,password from userinfo where username='"+username+"'")
            cur.execute("select username,password from userinfo where username='%s'"%username)
            data=cur.fetchall()  
            
            #if username not in userinfo:
            if len(data)==0:  
                #userinfo[username] = password
                cur.execute("insert into userinfo(username,password) values('%s','%s')"%(username,password))
                db.commit()
                cur.close()
                db.close()
                return redirect('/')
            
            cur.close()
            db.close()
    return render_template('register.html')

@app.route("/chat",methods=["GET","POST"])
def chat():
    ip = request.remote_addr
    if ip in dic_online:
        msg = request.args.get('message')
        print(msg)
        if msg != None and msg !="":
            a.append([dic_online[ip],msg])
        return render_template('chat.html',data = a , s = dic_online[ip] )
    else:
        return redirect('/')
    
@app.route("/logout",methods=["GET","POST"])
def logout():
    ip = request.remote_addr
    del dic_online[ip]
    return redirect('/')

if __name__ =="__main__":
    app.run(host='172.16.91.100',port=8080)
##    app.run(host='192.168.3.9',port=8080)
