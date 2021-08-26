import numpy as np

n = 1024
x = np.random.randint(low=-n,high=n,size=n)
y = np.random.randint(low=-n,high=n,size=n)

file = "data/input2.txt"
file = open(file,"w+",encoding="utf-8")
content = ""

for i in range(0,n):
    content += str(x[i]) + " " + str(y[i]) + "\n"

file.write(content)
file.close()