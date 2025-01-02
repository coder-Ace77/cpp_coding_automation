import random

def convert(line):
    return line.split()

def INTGEN(line):
    MIN = int(line[1])
    MAX = int(line[2])
    return str(random.randint(MIN,MAX))

def RANDOMINDEX(MAXN):
    return random.randint(0,MAXN)

def ARRGEN(line):
    N = int(line[1])
    NN = random.randint(1,N)
    ans=""
    ans+=str(NN)+"\n"

    if line[2][0]=="[":
        linearg = line[2][1:-1].split(",")
        for _ in range(NN):
            index =RANDOMINDEX(len(linearg)-1)
            ans+=linearg[index]+" "
    else:
        MIN = int(line[2])
        MAX = int(line[3])
        for _ in range(NN):
            ans+=str(random.randint(MIN,MAX))+" "
    return ans

def ARRGENC(line):
    N = int(line[1])
    NN = N
    ans=""
    ans+=str(NN)+"\n"

    if line[2][0]=="[":
        linearg = line[2][1:-1].split(",")
        for _ in range(NN):
            index =RANDOMINDEX(len(linearg)-1)
            ans+=linearg[index]+" "
    else:
        MIN = int(line[2])
        MAX = int(line[3])
        for _ in range(NN):
            ans+=str(random.randint(MIN,MAX))+" "
    return ans

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


def STRGEN(line):
    N = int(line[1])
    NN = random.randint(1,N)
    ans=""

    if line[2][0]=="[":
        linearg = line[2][1:-1]
        for _ in range(NN):
            ans+=RANDOMCHAR(linearg,True)
    else:
        for _ in range(NN):
            ans+=RANDOMCHAR(line[2])
    return ans

def STRGENN(line):
    N = int(line[1])
    NN = random.randint(1,N)

    ans=""
    ans+=str(NN)+"\n"
    if line[2][0]=="[":
        linearg = line[2][1:-1]
        for _ in range(NN):
            ans+=RANDOMCHAR(linearg,True)
    else:
        for _ in range(NN):
            ans+=RANDOMCHAR(line[2])
    return ans

def interpret(line):
    line = convert(line)
    gen=""
    if line[0]=="INT":
        gen+=INTGEN(line)
    elif line[0]=="ARR":
        gen+=ARRGEN(line)
    elif line[0]=="ARRC":
        gen+=ARRGENC(line)
    elif line[0]=="STR":
        gen+=STRGEN(line)
    elif line[0]=="STRN":
        gen+=STRGENN(line)
    return gen


# line  read
def read_file(file_path, interpret):
    with open(file_path, 'r') as file:
        ok=False
        ans={}
        ans[0]=0
        ans[2]=[]
        ans[1]=0
        for line in file:
            temp = line.strip()
            if temp:  
                if ok==False:
                    ans[0]= random.randint(1,int(temp.split(" ")[1]))
                    ans[1]= int(temp.split(" ")[2])
                    ok = True
                else: 
                    ans[2].append(temp)
    return ans

file_path="spec.txt"
spec = read_file(file_path,interpret)

test = ""
test+=str(spec[0])+"\n"

for _ in range(spec[0]):
    for i in range(spec[1]):
        test+=interpret(spec[2][i])+"\n"

print(test)
