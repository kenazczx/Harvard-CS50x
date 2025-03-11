from cs50 import get_float
# Only coins available are 1c, 5c, 10c, 25c
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

change = round(change * 100)
pennies = 0
nickels = 0
dimes = 0
quarters = 0

while change > 0:
    while change >= 25:
        quarters += 1
        change -= 25
    while change >= 10:
        dimes += 1
        change -= 10
    while change >= 5:
        nickels += 1
        change -= 5
    while change >= 1:
        pennies += 1
        change -= 1


print(quarters + dimes + nickels + pennies)
