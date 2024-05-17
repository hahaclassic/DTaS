import random

BRAND = [
    "BMW",
    "Rolls-Royce",
    "Mersedes-Benz",
    "Suzuki",
    "Peugeot",
    "Opel",
    "Jeep",
    "Alfa Romeo",
    "Fiat",
    "Maserati",
    "Ferrari",
    "Dodge",
    "RAM",
    "Honda",
    "Ford",
    "Lincoln",
    "Hyundai",
    "Kia",
    "Nissan",
    "Lada",
    "Infinity",
    "Lexus",
    "Audi",
    "Bentley",
    "Porshe",
    "Buggati",
    "Lamborghini"
]
COUNTRY = [
    "Russia",
    "USA",
    "UK",
    "China",
    "Japan",
    "South Korea",
    "Germany",
    "France",
    "India",
    "Italy",
    "Spain",
]
COLOR = [
    "red",
    "grey",
    "light blue",
    "dark blue",
    "green",
    "yellow",
    "pink",
    "silver",
    "gold",
    "orange",
    "brown",
    "white",
    "black",
    "purple"
]

count = 10000
f = open("./data/cars10000.txt", 'a')

for i in range(count):
    brand = BRAND[random.randint(0, len(BRAND)-1)]
    country = COUNTRY[random.randint(0, len(COUNTRY)-1)]
    color = COLOR[random.randint(0, len(COLOR)-1)] 
    price = random.randint(1000, 100000)
    service = random.randint(0,1)
    condition = random.randint(0,1)

    if condition:
        guarantee = random.randint(1,25)
        f.write(f"{brand}\n{country}\n{color}\n{price}\n{service}\n{condition}\n{guarantee}\n")
    else:
        year = random.randint(1950, 2023)
        mileage = random.randint(0, 1000000)
        repairs = random.randint(0, 20)
        owners = random.randint(1, 30)
        f.write(f"{brand}\n{country}\n{color}\n{price}\n{service}\n{condition}\n{year}\n{mileage}\n{repairs}\n{owners}\n")

f.close()
print("Done.")