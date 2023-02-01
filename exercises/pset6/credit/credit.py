from cs50 import get_string
while True:
    card = get_string("Number:")
    if(len(card) >= 13):
        if(len(card) <= 16):
            break
digit = 2
normal = 0
double = 0
for i in range(0,len(card)):
    if (digit % 2 == 0):
        normal += ord(card[len(card) - i - 1]) - 48
        digit+= 1
    elif ((ord(card[len(card) - i - 1]) - 48) * 2 > 9):
        double += (((ord(card[len(card) - i - 1]) - 48) * 2) % 10) + (((ord(card[len(card) - i - 1]) - 48) * 2) - (((ord(card[len(card) - i - 1]) - 48) * 2) % 10)) // 10
        digit += 1
    else:
        double += (ord(card[len(card) - i - 1]) - 48) * 2
        digit += 1
if ((double + normal) % 10 != 0):
    print("INVALID")
elif (((ord(card[0])-48) * 10 + (ord(card[1]) - 48)) == 37):
    print("AMEX")
elif (((ord(card[0])-48) * 10 + (ord(card[1]) - 48)) > 50 and ((ord(card[0])-48) * 10 + (ord(card[1]) - 48)) < 56):
    print("MASTERCARD")
else:
    print("VISA")