import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")
months = {
        1: "Janeiro",
        2: "Fevereiro",
        3: "Março",
        4: "Abril",
        5: "Maio",
        6: "Junho",
        7: "Julho",
        8: "Agosto",
        9: "Setembro",
        10: "Outubro",
        11: "Novembro",
        12: "Dezembro"
        }

@app.route("/", methods=["GET", "POST"])
def index():
    table = db.execute("SELECT * FROM birthdays")
    rows = 0
    for row in table:
        rows += 1
    if request.method == "POST":
        if (request.form.get("month") == None) or (request.form.get("day") == None) or not((request.form.get("name"))):
            return render_template("index.html", code = 2, months = months, table = table, rows = rows)
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if len(db.execute("SELECT * FROM birthdays WHERE name LIKE ?", name)) > 0:
            return render_template("index.html", code = 1, months = months, table = table, rows = rows)
        else:
            db.execute("INSERT INTO birthdays(name, month, day) VALUES(?, ?, ?)", name, month, day)
        # TODO: Add the user's entry into the database
    table = db.execute("SELECT * FROM birthdays")
    # TODO: Display the entries in the database on index.html
    rows = 0
    for row in table:
        rows += 1
    return render_template("index.html", code = 0, months = months, table = table, rows = rows)

