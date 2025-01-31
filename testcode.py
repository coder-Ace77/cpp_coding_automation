import random

MAXN = 10
MAXINT = 10
MININT = 1
T = 2

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

class DSU:
    def __init__(self,n):
        self.n = n
        self.par = [i for i in range(n)]
        self.size = [1]*n
        self.c = n
    
    def find(self,a):
        if(self.par[a]==a):
            return a
        else:
            self.par[a]=self.find(self.par[a])
            return self.par[a]
    
    def unite(self,a,b):
        a=self.find(a)
        b=self.find(b)
        if(a!=b):
            if self.size[a]<self.size[b]:
                a,b=b,a
            self.par[b]=a
            self.size[a]+=self.size[a]
            self.c-=1



def gen_random_tree(n):
    d = DSU(n)
    while d.c>1:
        u = random.randint(1,n)
        v = random.randint(1,n)
        if d.find(u-1)!=d.find(v-1):
            d.unite(u-1,v-1)
            print(u,v)


# t = random.randint(1, T)
# print(t)

n = random.randint(1, MAXN)
print(n)
gen_random_tree(n)
for _ in range(n):
    print(random.randint(MININT,MAXINT),end=" ")
