import csv
from cs50 import SQL
from sys import argv


def main():
    # Check command line line argument, if it is valid, it
    # returns and assigns house name to a variable house
    house = check_argv()

    # Connect to a database and get data, then asign it to a variable
    data = query(house)

    # Processes recieved data and prints results
    process_and_output_data(data)


def check_argv():

    houses = ['Gryffindor', 'Slytherin', 'Ravenclaw', 'Hufflepuff']

    if len(argv) != 2:
        print("Usage: python3 roster.py [house]")
        exit(1)
    elif argv[1].title() not in houses:
        print("Usage: python3 roster.py [house]")
        exit(2)

    house = argv[1].title()

    return house


def query(house):

    db = SQL('sqlite:///students.db')

    data =  db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

    return data

# recieve separated list of name, process and join it into one string
def process_name(name):

    if name[1] == None:
        del name[1]

    processed_name = ' '.join(name)

    return processed_name


def process_and_output_data(data):

    for student in data:
        name = process_name([student['first'], student['middle'], student['last']])
        birth = student['birth']

        print(f"{name}, born {birth}")


if __name__ == "__main__":
    main()