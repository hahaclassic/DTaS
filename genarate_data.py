import random

k = int(input("Введите количество файлов: "))

f = open("./data/" + str(k) + ".txt", "w")

names = []
attributes = ["-rwxrwxrwx", "-rwxr--r--", "-r--r--r--", "-rwx--x--x", "-rwxr-x--x", "-r-xr-xr--"]

letters = "absdefghijklmnopqrstuvwxyz"
letters += letters.upper()
l = len(letters)

i = 0

f.write(str(k) + "\n")

while i < k:
    name = []
    l_name = random.randint(1, 10)
    for z in range (0, l_name):
        name.append(random.choice(letters))
    
    str_name = ''.join(name)
    if (str_name not in names):
        names.append(str_name)
    
        day = random.randint(1, 31)
        month = random.randint(1, 12)
        year = random.randint(2000, 2023)
        hour = random.randint(0, 23)
        minutes = random.randint(0, 59)
        attr = random.choice(attributes)

        f.write(attr + " " + str(day) + "." + str(month) + "." + str(year) + " " + str(hour) + ":" + str(minutes) + " " + str_name + "\n")
        i += 1
    
f.close()