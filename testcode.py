import random

T = 2
MAXN = 5
MAXINT = 5
MININT = 1

def RANDOMCHAR(arg,isSet=False):
    if isSet:
        return str(random.choices(arg)[0])
    if arg=="a":
        choices = "abcdefghijklmnopqrstuvwxyz"
    elif arg=="A":
        choices="ABCDEFGHIJKLMNOPQRSTUV"
    else:
        choices="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUV"
    return str(random.choices(choices)[0])

t = random.randint(1,T)
print(t)
for _ in range(t):
    n = random.randint(1,MAXN)
    m = random.randint(1,MAXN)
    x = random.randint(1,n)
    y = random.randint(1,m)
    d = random.randint(0,n+m)
    print(n,m,x,y,d)
    # l = []
    # for _ in range(n):
    #     val = random.randint(MININT,MAXINT-1)
    #     l.append(val)
    #     print(val,end=" ")
    # print()
    # for i in range(n):
    #     val = random.randint(l[i]+1,MAXINT)
    #     print(val,end=" ")
    # print()




