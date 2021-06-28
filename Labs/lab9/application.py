import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")



def check_data(month, day):
    # validating input. If month is digit and 1 >= month >= 12 and
    # if day is digit and 1 >= day >= 31 function returns true
    condition = (month.isdigit() and int(month) in range(1,13)) \
                and (day.isdigit() and int(day) in range(1,32))
    return condition


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        operation = request.form.get('submit')

        name = request.form.get('name')
        month = request.form.get('month')
        day = request.form.get('day')

        if check_data(month, day):
            if operation == 'Add birthday':
                db.execute('INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)', name, month, day)
            else:
                db.execute('DELETE FROM birthdays WHERE name = ? AND month = ? AND day = ? LIMIT 1', name, month, day)
        else:
            return redirect('/error')

        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        data = db.execute('SELECT * FROM birthdays')

        return render_template("index.html", data=data)

@app.route('/error')
def error_page():
    return render_template("error.html")