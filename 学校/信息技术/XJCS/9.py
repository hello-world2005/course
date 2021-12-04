def Code2Char(c):  #十进制值转换为加密字符的函数
    s='IlikeCHNpostcard'
    return s[c]
s=input()
n = len(s)
ss=''
for i in range(n):
    a=ord(s[i])
    b1=a//16
    b2=a%16
    ss+=Code2Char(b1)+Code2Char(b2)  
print(ss)

