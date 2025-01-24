import random

MAXN = 10
MAXINT = 10
MININT = 1
T = 1

# def RANDOMCHAR(arg,isSet=False):
#     if isSet:
#         return str(random.choices(arg)[0])
#     if arg=="a":
#         choices = "abcdefghijklmnopqrstuvwxyz"
#     elif arg=="A":
#         choices="ABCDEFGHIJKLMNOPQRSTUV"
#     else:
#         choices="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUV"
#     return str(random.choices(choices)[0])


# t = random.randint(1,T)
# print(t)
# for _ in range(t):
#     n = random.randint(1,MAXN)
#     m = random.randint(1,MAXN)
#     x = random.randint(1,n)
#     y = random.randint(1,m)
#     d = random.randint(0,n+m)
#     print(n,m,x,y,d)
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

def RANDOMCHAR():
    choices="RGB"
    return str(random.choices(choices)[0])

t = random.randint(1, T)
print(t)
print()

class DSU:
    def __init__(self, n):
        self.par = list(range(n))
        self.size = [1] * n
        self.c = n

    def find(self, a):
        if self.par[a] == a:
            return a
        else:
            self.par[a] = self.find(self.par[a])  
            return self.par[a]
        
    def unite(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a != b:
            if self.size[a] < self.size[b]:
                a, b = b, a
            self.par[b] = a
            self.size[a] += self.size[b]
            self.c -= 1

for _ in range(t):
    n = random.randint(2, MAXN)
    print(n)
    dsu = DSU(n)
    while dsu.c > 1:
        a = random.randint(0, n - 1)  
        b = random.randint(0, n - 1)  
        if(dsu.find(a)!=dsu.find(b)):
            dsu.unite(a, b)
            print(a+1,b+1)

