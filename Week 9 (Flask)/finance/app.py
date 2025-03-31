import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """TODO: Show portfolio of stocks"""
    user_id = session.get("user_id")
    stocks = db.execute(
        "SELECT stock, SUM(shares) AS shares FROM stocks WHERE user_id = ? GROUP BY stock, user_id", user_id)
    portfolio = []
    for stock in stocks:
        symbol = stock["stock"]
        shares = stock["shares"]
        quote = lookup(symbol)
        current_price = quote["price"]
        total_value = round(current_price * shares, 2)
        portfolio.append({
            "symbol": symbol,
            "shares": shares,
            "price": current_price,
            "usd_price": usd(current_price),
            "total": total_value,
            "usd_total": usd(total_value)
        })
    cash_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = float(cash_dict[0]["cash"])
    total = cash
    for row in portfolio:
        total += float(row["total"])
    return render_template("index.html", stocks=portfolio, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """TODO: Buy shares of stock"""
    if request.method == "POST":
        buy_stock = request.form.get("symbol")
        buy_shares = request.form.get("shares")
        if not buy_stock:
            return apology("must provide a stock symbol", 400)
        if not buy_shares:
            return apology("must provide amount of shares", 400)
        try:
            check_shares_int = int(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be in whole numbers", 400)
        if int(buy_shares) <= 0:
            return apology("input a positive amount of shares to buy!", 400)
        stock = lookup(buy_stock)
        if stock == None:
            return apology("stock does not exist", 400)
        price = float(stock["price"])
        shares = float(buy_shares)
        user_id = session.get("user_id")
        cash_dict = db.execute("SELECT cash FROM users WHERE id= ?", user_id)
        cash = float(cash_dict[0]["cash"])
        total_price = price * shares
        if total_price > cash:
            return apology("sorry you can't afford it", 400)
        else:
            owned_stock = db.execute(
                "SELECT * FROM stocks WHERE user_id = ? AND stock = ?", user_id, buy_stock)
            if owned_stock:
                own_shares = db.execute(
                    "SELECT SUM(shares) AS shares FROM stocks WHERE user_id = ? AND stock = ? GROUP BY stock, user_id", user_id, buy_stock)
                owned_shares = own_shares[0]["shares"]
                new_shares = owned_shares + shares
                db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND stock = ?",
                           new_shares, user_id, buy_stock)
            else:
                db.execute("INSERT INTO stocks (user_id, stock, shares, bought_price) VALUES (?, ?, ?, ?)",
                           user_id, buy_stock, shares, price)
            db.execute("INSERT INTO history (user_id, stock, shares, price, transaction_type) VALUES (?, ?, ?, ?, 'buy')",
                       user_id, buy_stock, shares, price)
            final_cash = cash - total_price
            db.execute("UPDATE users SET cash = ? WHERE id = ?", final_cash, user_id)
            flash("Stock Bought Successfully!", "success")
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """TODO: Show history of transactions"""
    user_id = session.get("user_id")
    historys = db.execute(
        "SELECT stock, shares, price, transaction_type, transaction_time FROM history WHERE user_id = ?", user_id)
    for history in historys:
        history["price"] = usd(float(history["price"]))
    return render_template("history.html", historys=historys)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """TODO: Get stock quote."""
    if request.method == "POST":
        quote_stock = request.form.get("symbol")
        if not quote_stock:
            return apology("must provide a stock symbol", 400)
        stock = lookup(quote_stock)
        if stock == None:
            return apology("stock does not exist", 400)
        stock_name = stock["name"]
        stock_price = stock["price"]
        return render_template("quoted.html", stock_name=stock_name, stock_price=usd(stock_price), quote_stock=quote_stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """TODO: Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        hash_password = generate_password_hash(password)
        if not name:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if password != confirmation:
            return apology("passwords don't match", 400)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, hash_password)
        except ValueError:
            return apology("username already taken", 400)
        flash("Registered Successfully!", "success")
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """TODO: Sell shares of stock"""
    if request.method == "POST":
        user_id = session.get("user_id")
        sell_stock = request.form.get("symbol")
        sell_shares = request.form.get("shares")
        if not sell_stock:
            return apology("input the stock to sell!", 400)
        if not sell_shares:
            return apology("input the amount of shares to sell!", 400)
        if int(sell_shares) <= 0:
            return apology("input a positive amount of shares to sell!", 400)
        try:
            check_shares_int = int(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be in whole numbers", 400)
        cash_dict = db.execute("SELECT cash FROM users WHERE id= ?", user_id)
        cash = float(cash_dict[0]["cash"])
        stock = lookup(sell_stock)
        price = float(stock["price"])
        shares = int(sell_shares)
        total_price = price * shares
        own_shares = db.execute(
            "SELECT SUM(shares) AS shares FROM stocks WHERE user_id = ? AND stock = ? GROUP BY stock, user_id", user_id, sell_stock)
        owned_shares = own_shares[0]["shares"]
        if owned_shares >= shares:
            if owned_shares == shares:
                db.execute("DELETE FROM stocks WHERE user_id = ? AND stock = ?", user_id, sell_stock)
            else:
                new_shares = owned_shares - shares
                db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND stock = ?",
                           new_shares, user_id, sell_stock)
            db.execute("INSERT INTO history (user_id, stock, shares, price, transaction_type) VALUES (?, ?, ?, ?, 'sell')",
                       user_id, sell_stock, shares, price)
            final_cash = cash + total_price
            db.execute("UPDATE users SET cash = ? WHERE id = ?", final_cash, user_id)
        else:
            return apology("Not enough shares to sell.", 400)
        flash("Stock Sold Successfully!", "success")
        return redirect("/")
    else:
        user_id = session.get("user_id")
        stocks = db.execute(
            "SELECT stock, SUM(shares) AS shares FROM stocks WHERE user_id = ? GROUP BY stock, user_id", user_id)
        return render_template("sell.html", stocks=stocks)


@app.route("/change", methods=["GET", "POST"])
@login_required
def change_password():
    """TODO: Change user's password"""
    if request.method == "POST":
        old_password = request.form.get("password_old")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        hash_password = generate_password_hash(password)
        user_id = session.get("user_id")
        if not old_password:
            return apology("must provide old password", 400)
        if not password:
            return apology("must provide new password", 400)
        if password != confirmation:
            return apology("passwords don't match", 400)
        hash_db_dict = db.execute("SELECT hash FROM users WHERE id = ?", user_id)
        hash_db = hash_db_dict[0]["hash"]
        if not check_password_hash(hash_db, old_password):
            return apology("Old password entered is wrong", 400)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hash_password, user_id)
        flash("Password Changed Successfully!", "success")
        return redirect("/")

    else:
        return render_template("change.html")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def add_cash():
    """TODO: Add Cash to User's Account"""
    if request.method == "POST":
        user_id = session.get("user_id")
        cash_amount_add = request.form.get("cash_amount")
        if not cash_amount_add:
            return apology("Add Valid Amount of Cash", 400)
        cash_dict = db.execute("SELECT cash FROM users WHERE id= ?", user_id)
        cash = float(cash_dict[0]["cash"])
        final_cash = cash + float(cash_amount_add)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", final_cash, user_id)
        flash("Cash Added Successfully!", "success")
        return redirect("/")
    else:
        return render_template("addcash.html")
