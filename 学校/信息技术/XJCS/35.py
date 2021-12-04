a = int(input())
b = int(input())
c = input()

if c == '+':
    print(a + b)
elif c == '-':
    print(a - b)
elif c == '*':
    print(a * b)
elif c == '/':
    if b != 0:
        print(int(a / b))
    else:
        print('Divided by zero!')
else:
    print('Invalid operator!')