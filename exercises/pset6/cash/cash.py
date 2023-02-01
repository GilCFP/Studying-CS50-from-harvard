from cs50 import get_float
while True:
    change = get_float("Change owed:")
    if change > 0:
        break
change *= 100
a = int(change/25)
count = a
change = change - a * 25
b = int(change/10)
count += b
change = change - b * 10
c = int(change/5)
count += c
change = change - c * 5
d = int(change/1)
count += d
change = change - d
print(f"{count}")