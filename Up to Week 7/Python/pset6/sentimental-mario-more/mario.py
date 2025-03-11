from cs50 import get_int

# Get user input
while True:
    height = get_int("Height: ")
    if height <= 8 and height >= 1:
        break


row = 0
# Print for each row
for i in range(height):
    print(" " * (height - row - 1), end="")
# Print Left Hash
    for i in range(row + 1):
        print("#", end="")
    # Print space
    print("  ", end="")
    # Print right Hash
    for i in range(row + 1):
        print("#", end="")
    print()
    row += 1
