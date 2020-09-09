from cs50 import get_float

while True:
    dollar_owed = get_float("Change owed: ")
    print(dollar_owed)
    cent_owed = (round(dollar_owed * 100, 2))
    if (cent_owed > 0):
        break

a = cent_owed // 25
b = (cent_owed % 25) // 10
c = ((cent_owed % 25) % 10) // 5
d = ((cent_owed % 25) % 10) % 5
print((int)(a + b + c + d))
