import csv
from cs50 import SQL
from sys import argv
from os import path

def main():
    # Check command line argument and return csv file name if it's valid
    csv_name = check_arg()

    # Connect to a database
    db = SQL("sqlite:///students.db")

    # Open csv
    with open(csv_name, 'r') as csv_file:
        # counter to skip reading column names from csv in a for loop
        n = 0

        # read data
        csv_data = csv.reader(csv_file)

        # read process and insert data from csv to students.db
        for row in csv_data:
            if n == 0:
                n = 1
                continue

            row = process_row(row)

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", row)

            n = 1


# check command line argument and return csv file name if it is valid
def check_arg():

    if len(argv) != 2:
        print("Usage: python3 import.py [file.csv]")
        exit(1)
    elif argv[1][-4:] != '.csv':
        print("Usage: python3 import.py [file.csv]")
        exit(2)

    # Assign csv file name to a variable csv_name
    csv_name = argv[1]

    # Check file  existance
    file_exists = path.isfile(csv_name)

    if not file_exists:
        print("File does not exist")
        exit(3)

    return csv_name


# process a single csv row
def process_row(csv_row):

    fullname = csv_row[0].split()

    if len(fullname) == 2:
        fullname.insert(1, None)

    processed_data = fullname + csv_row[1:]

    return processed_data

if __name__ == "__main__":
    main()