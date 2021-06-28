import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd, check_pass, remove_empty_stocks

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
def index():
    """Show portfolio of stocks"""
    user_id = session['user_id']

    # get user ballance and select stock data from database
    ballance = db.execute('SELECT cash FROM users WHERE id=?', session['user_id'])[0]['cash']
    data = db.execute('SELECT symbol, company, SUM(quantity) FROM buyments GROUP BY symbol HAVING userid=?', user_id)

    # remove stocks with 0 quantity from recieved data
    remove_empty_stocks(data)

    # list to collect all prices of stocks
    stock_prices = []

    # process and initialize stock data into a list of dictionaries
    for stock in data:
        # get current price of stock
        price = lookup(stock['symbol'])['price']

        # get total stock price (price * quantity)
        stock_total_price = price * stock['SUM(quantity)']

        stock_prices.append(stock_total_price)
        # asssign price and total values to stock dictionary data
        stock['total'] = usd(stock_total_price)
        stock['price'] = usd(price)

    # calculate total property value
    total_property = sum(stock_prices) + ballance

    return render_template('index.html', data=data, cash=usd(ballance), total=usd(total_property))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        # get form data
        symbol = request.form.get('symbol').upper()
        shares = request.form.get('shares')

        # check if data is provided and convert quantity of shares to int
        if not symbol:
            return apology("must enter symbol")
        elif not shares:
            return apology('must enter quantity')
        # check if shares is integer
        elif not shares.isdigit():
            return apology("Number must be positive integer")
        # convert shares to int
        shares = int(shares)

        # search result
        result = lookup(symbol)

        # check if result is received
        if result:
            # get user ballance and total money to pay
            user_id = session['user_id']
            user_cash = db.execute('SELECT cash FROM users WHERE id=?', user_id)[0]['cash']
            total_pay = result['price'] * shares

            # check if user ballance is enough
            if user_cash < total_pay:
                return apology('Sorry, you have not enough money')

            # buying
            left_money = user_cash - total_pay
            db.execute('UPDATE users SET cash= ? WHERE id=?', left_money, user_id)

            time = datetime.now().strftime('%Y/%m %H:%M:%S')

            db.execute('INSERT INTO buyments (userid, symbol, company, quantity, price, date) \
                        VALUES(?, ?, ?, ?, ?, ?)',
                       user_id, symbol, result['name'], shares, result['price'], time)

            return redirect('/')
        else:
            return apology('Invalid symbol')

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session['user_id']
    data = db.execute('SELECT symbol, quantity, price, date FROM buyments WHERE userid=? ORDER BY date', user_id)
    # convert cash data to usd
    for stock in data:
        stock['price'] = usd(stock['price'])
    return render_template('history.html', data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

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
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get('symbol')

        result = lookup(symbol)

        if result:
            result_text = f"A share of {result['name']} ({result['symbol']}) is {usd(result['price'])}"

            return render_template("quoted.html", result=result_text)
        else:
            return apology("Invalid symbol")

    else:
        return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # initialize form data
        username = request.form.get("username")
        password = request.form.get("password")
        repassword = request.form.get("confirmation")

        # validate input
        if not username:
            return apology("must provide username")
        elif not password:
            return apology("must provide password")
        elif not repassword:
            return apology("must re-enter password")
        elif password != repassword:
            return apology("Passwords does not match")

        # check if username already exists
        check_username = db.execute('SELECT * FROM users WHERE username=?', username)
        if check_username:
            return apology("username has already been taken")

        if not check_pass(password):
            return apology('Your password must contain (8-20) characters, uppercase and lowercase letter, number and special character')

        # generate pass hash
        pass_hash = generate_password_hash(password)

        # insert user data in database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, pass_hash)

        # Create session and login
        session["user_id"] = db.execute('SELECT id FROM users WHERE username=?', username)[0]['id']

        flash('You were successfully registered!')

        return redirect('/')
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session['user_id']
    """Sell shares of stock"""
    # get user stock data and ballance
    stocks = db.execute("SELECT symbol, SUM(quantity) FROM buyments GROUP BY symbol HAVING userid=?", user_id)
    ballance = db.execute('SELECT cash FROM users WHERE id=?', user_id)[0]['cash']

    # initialize stock data in dictionary
    stock_data = {}
    for stock in stocks:
        stock_data[stock['symbol']] = stock['SUM(quantity)']

    if request.method == 'POST':
        # get form data
        stock_name = request.form.get('symbol')
        stock_quantity = request.form.get('shares')

        # check if symbol existance and validity then convert it to uppercase
        if not stock_name:
            return apology('must select symbol')
        elif not stock_name in stock_data:
            return apology("You do not any shares of that stock")
        stock_name = stock_name.upper()

        # check if quantity is valid and convert to int
        if not stock_quantity.isdigit():
            return apology("must select positive integer")
        stock_quantity = int(stock_quantity)

        if stock_quantity < 1:
            return apology('must select positive integer')
        elif stock_quantity > stock_data[stock_name]:
            return apology('You do not have this number of stock shares.')
        stock_quantity = int(stock_quantity)

        # sell operation
        time = datetime.now().strftime('%Y/%m %H:%M:%S')
        # search for latest stock data
        current_stock_data = lookup(stock_name)
        company = current_stock_data['name']
        # calculate full price
        current_ballance = current_stock_data['price'] * stock_quantity + ballance
        current_ballance = float(f"{current_ballance:.2f}")

        # update database
        db.execute("INSERT INTO buyments (userid, symbol, company, quantity, price, date) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, stock_name, company, -stock_quantity, current_stock_data['price'], time)

        db.execute('UPDATE users SET cash=? WHERE id=?', current_ballance, user_id)

        return redirect('/')

    else:
        # if number of quantity is 0, stock dictionary  is removed from recieved data
        remove_empty_stocks(stocks)

        stock_names = []
        for stock in stocks:
            stock_names.append(stock['symbol'])

        return render_template('sell.html', stocks=stock_names)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
