from cs50 import get_int
i = get_int("Height:")
while i > 8 or i < 1:
    i = get_int("Height:")
for j in range(i):
    print(" " * (i - j - 1), end = '')
    print("#" * (j + 1),end='')
    print()