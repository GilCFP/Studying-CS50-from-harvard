import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():#shows portfolio
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?",session["user_id"])
    balance = float(db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash'].replace("$", "").replace(",", ""))
    total_balance = balance
    rows = 0
    for row in stocks:
        stocks[rows]['name'] = lookup(row['symbol'])['name']
        stocks[rows]['price'] = usd(lookup(row['symbol'])['price'])
        stocks[rows]['total'] = usd(lookup(row['symbol'])['price'] * row['quantity'])
        total_balance += lookup(row['symbol'])['price'] * row['quantity']
        rows+=1
    return render_template("index.html", stocks = stocks, rows = rows, total_balance = usd(total_balance), balance = usd(balance))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():#buy some amount of stocksm, update cash(users), stocks table and history table
    """Buy shares of stock"""

    table = db.execute("SELECT cash FROM users where id = ?",session["user_id"])
    for row in table:
        balance = round(float(table[0]['cash'].replace("$", "").replace(",", "")),2)
    if request.method == "GET":
        return render_template("buy.html", balance = table[0]['cash'])
    else:
        if not check_password_hash(db.execute("SELECT hash FROM users WHERE id = ?",session['user_id'])[0]['hash'], request.form.get("password")):
            return apology("Wrong Password")
        if not request.form.get("symbol"):
            return apology("Empty name it'sn't acceptable")
        if not request.form.get("shares"):
            return apology("Empty amount it'sn't acceptable")
        result = lookup(request.form.get("symbol"))
        if result == None:
            return apology("That's not an stock name")
        quantity = int(request.form.get("shares"))
        if result['price'] * quantity > balance:
            return apology("Insufficient balance")
        symbol_present = False
        for row in db.execute("SELECT symbol FROM stocks WHERE user_id = ?",session["user_id"]):
            if row['symbol'] == lookup(request.form.get("symbol"))['symbol']:
                symbol_present = True
            break
        if symbol_present:
            current = db.execute("SELECT quantity FROM stocks WHERE(user_id = ? AND symbol LIKE ?)", session["user_id"], request.form.get("symbol"))
            db.execute("UPDATE stocks SET quantity = ? WHERE(user_id = ? AND symbol LIKE ?)", current[0]['quantity'] + int(request.form.get("shares")), session["user_id"], request.form.get("symbol"))
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, quantity, value, total) VALUES(?, ?, ?, ?, ?);",
                session["user_id"], result['symbol'], quantity, result['price'], result['price'] * quantity)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", usd(balance - result['price'] * quantity), session["user_id"])
        db.execute("INSERT INTO history (user_id, type, symbol, amount, price, total) VALUES(?, 'buy', ?, ?, ?, ?);",
            session['user_id'], result['symbol'], quantity, result['price'], result['price'] * quantity,)
        return redirect("/")


@app.route("/history")
@login_required
def history():#shows a table based on the table history
    """Show history of transactions"""
    if len(db.execute("SELECT * FROM stocks WHERE user_id = ?",session["user_id"])) == 0:
        return render_template("history.html",visibility = 'collapse', rows = 0)
    result = db.execute("SELECT * FROM history WHERE user_id = ?",session["user_id"])
    rows = 0
    for row in result:
        result[rows]["price"] = usd(row['price'])
        result[rows]["price"] = usd(row['total'])
        rows += 1
    return render_template("history.html",rows = rows, result = result)



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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
def quote():#look for a determined action on the database and exhibits it in a table
    if request.method == "POST":
        if (lookup(request.form.get("symbol"))) == None:
            return apology("That's not a stock symbol")
        result = (lookup(request.form.get("symbol")))
        visibility = 'visible'
        return render_template("quote.html", name_stock = result['name'], price_stock = usd(result['price']), symbol_stock = result['symbol'], visibility = visibility)
    else:
        visibility = 'collapse'
        return render_template("quote.html", visibility = visibility)


@app.route("/register", methods=["GET", "POST"])
def register():#insert in finance.db table users and redirect to login
    if request.method == "POST":    #processing input from user and redirecting to login
        if not request.form.get("username"):    #empty username
            return apology("Empty user names are invalid")
        if not request.form.get("password"):    #empty password
            return apology("Empty passwords are invalid")
        if request.form.get("password") != request.form.get("confirmation"):    #confirm password wrong
            return apology("The passwords must combine")
        if not db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username")): #verify if useranme already in use
            db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")), usd(10000))
            return redirect("/login") #redirect to the login page
        else:
            return apology("Username already registered")
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():#decrease the amount of the selected stock and delete the row if de amount turs it in 0
    if request.method == "GET":
        stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?",session["user_id"])
        if len(stocks) == 0:
            return redirect("/")
        balance = float(db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash'].replace("$", "").replace(",", ""))
        rows = 0
        for row in stocks:
            stocks[rows]['name'] = lookup(row['symbol'])['name']
            stocks[rows]['price'] = usd(lookup(row['symbol'])['price'])
            stocks[rows]['total'] = usd(lookup(row['symbol'])['price'] * row['quantity'])
            rows+=1
        return render_template("sell.html", stocks = stocks, rows = rows, balance = usd(balance))
    else:
        if not check_password_hash(db.execute("SELECT hash FROM users WHERE id = ?",session['user_id'])[0]['hash'], request.form.get("password")):
            return apology("Wrong Password")
        if not request.form.get("symbol"):
            return apology("Empty name it'sn't acceptable")
        if not request.form.get("shares"):
            return apology("Empty amount it'sn't acceptable")
        result = lookup(request.form.get("symbol"))
        if result == None:
            return apology("That's not an stock name")
        quantity = int(request.form.get("shares"))
        verifier = db.execute("SELECT quantity FROM stocks WHERE(user_id = ? AND symbol LIKE ?)", session['user_id'],request.form.get("symbol"))
        if len(verifier) == 0:
            return apology("Insufficient amount of shares")
        print(verifier[0]['quantity'])
        if quantity > verifier[0]['quantity']:
            return apology("Insufficient amount of shares")
        balance = round(float(db.execute("SELECT cash FROM users where id = ?",session["user_id"])[0]['cash'].replace("$", "").replace(",", "")),2)
        db.execute("UPDATE users SET cash = ? WHERE(id = ?)", usd(balance + quantity * result['price']), session['user_id'])
        db.execute("UPDATE stocks SET quantity = quantity - ? WHERE(user_id = ? AND symbol LIKE ?)", request.form.get("shares"),session['user_id'], request.form.get("symbol"))
        if int(db.execute("SELECT quantity FROM stocks WHERE(user_id = ? AND symbol LIKE ?)", session['user_id'], request.form.get("symbol"))[0]['quantity']) == 0:
            db.execute("DELETE FROM stocks WHERE(user_id = ? AND symbol LIKE ?)", session['user_id'], request.form.get("symbol"))
        db.execute("INSERT INTO history (user_id, type, symbol, amount, price, total) VALUES(?, 'sell', ?, ?, ?, ?);",
            session['user_id'], result['symbol'], quantity, result['price'], result['price'] * quantity,)
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
