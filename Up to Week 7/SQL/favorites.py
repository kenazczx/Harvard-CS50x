from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE language = ?", favorite)

rows = rows[0]

print(rows["n"])
