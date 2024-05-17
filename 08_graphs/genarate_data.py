import random

k = int(input("Введите количество вершин: "))

f = open("./data/" + str(k) + ".txt", "w")

f.write(str(k) + "\n")

for i in range(k):
    for j in range(k):
        t = random.randint(0, k - 1)
        if t == 0:
            f.write(str(random.randint(1, 100)) + " ")
        else:
            f.write("0 ")
    f.write("\n")
    
f.close()
