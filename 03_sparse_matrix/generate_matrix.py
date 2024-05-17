import random
count = int(input("n: "))
fullness = int(input("fullness (%): ")) # % ненулевых элементов
zeros = int(count / 100 * (100 - fullness))

file = "m" + str(count) + "_" + str(fullness)
f = open("./data/" + file, 'w')
f.write(f"{count} {count}\n")

for i in range(count):
    z = [0] * zeros
    nz = []
    for i in range(count - zeros):
        nz.append(random.randint(1, 1000))

    row = z + nz
    random.shuffle(row)

    for j in range(count):
        f.write(f"{row[j]} ")

    f.write("\n")

f.close()
print("Done.")