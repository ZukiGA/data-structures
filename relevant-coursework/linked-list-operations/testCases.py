import random
n=10000
array=random.sample(range(0,100000),n)
array2=random.sample(range(0,100000),n)

f = open("result.txt","w")

f.write(str(n)+'\n')
for i in range(n):
	f.write(str(array[i])+"\n")

f.write(str(n)+'\n')
for i in range(n):
	f.write(str(array[i])+"\n")

f.close()