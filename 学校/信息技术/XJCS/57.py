n = int(input())

server = dict()


def Ip(ip):
    _ = ip
    ip = int(ip)
    if (str(ip) != _):
        return True
    if ip >= 0 and ip <= 255:
        return False
    return True


def Port(port):
    _ = port
    port = int(port)
    if (str(port) != _):
        return True
    if port >= 0 and port <= 65535:
        return False
    return True


def Check(s):
    l1 = len(s.split(':'))
    if (l1 != 2 or s.split(':')[0] == '' or s.split(':')[1] == ''):
        return False
    qwq1 = s.split(':')[0]
    qwq2 = s.split(':')[1]
    if '.' in qwq2:
        return False
    l2 = len(qwq1.split('.'))
    qwe = qwq1.split('.')
    # print(qwe)
    if (l2 != 4 or qwe[0] == '' or qwe[1] == '' or qwe[2] == '' or qwe[3] == ''):
        return False
    return True

for i in range(n):
    ss = input()
    s = ss.split(' ')
    if not Check(s[1]):
        print('ERR')
        continue
    ip = s[1].split(':')[0].split('.')
    port = s[1].split(':')[1]
    #print(ip, port)
    if (Ip(ip[0]) or Ip(ip[1]) or Ip(ip[2]) or Ip(ip[3]) or Port(port)):
        print('ERR')
        continue
    s = ss.split(' ')[1]
    # print(s[0])
    if (ss[0][0] == 'S'):
        if not (s in server):
            server[s] = i + 1
            print('OK')
        else:
            print('FAIL')
    if (ss[0][0] == 'C'):
        if not (s in server):
            print('FAIL')
        else:
            print(server[s])
