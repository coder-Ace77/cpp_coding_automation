from math import factorial

n=7
for i in range(n):
    print("I: ",i)
    for j in range(10):
        num = int(str(j)*factorial(i))
        if(num%7==0):   
            print(num)