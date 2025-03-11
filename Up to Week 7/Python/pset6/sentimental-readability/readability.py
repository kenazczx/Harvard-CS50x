# Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8

from cs50 import get_string

input = get_string("Text: ")

letters = 0
words = 1
sentences = 0

for char in input:
    if char.isalpha():
        letters += 1
    elif char == " ":
        words += 1
    elif char in [".", "?", "!"]:
        sentences += 1

coleman = round(0.0588 * ((100 * letters) / words) - 0.296 * ((100 * sentences) / words) - 15.8)
if coleman < 1:
    print("Before Grade 1")
elif coleman >= 16:
    print("Grade 16+")
else:
    print(f"Grade {coleman}")
