from sys import argv, exit
import csv
import re

# Check number of command-line arguments
if len(argv) != 3:
    print("Usage: python dna.py [Database.csv] [DNA_sequence.txt]")
    exit(0)

# Validate command-line arguments
if argv[1][-4:] != '.csv' or argv[2][-4:] != '.txt':
    print("Usage: python dna.py [Database.csv] [DNA_sequence.txt]")
    exit(1)

# class DNA which does all work to determine owner of DNA sample


class DNA:

    def __init__(self):
        # Load data
        self.sequence = self.load_sequence()
        self.database = self.load_database()
        # slices list of STRs from database
        self.STRs = self.database[0][1:]
        # determine owner of DNA sample
        self.DNA_sample_owner = self.determine()

    # Load DNA sequence as string from command-line argument (sequence).txt
    def load_sequence(self):
        with open(argv[2], 'r') as dna_sequence:
            sequence = dna_sequence.read()
        return sequence

    # Load csv DNA database as 2D list from command-line argument (database).csv
    def load_database(self):
        with open(argv[1], 'r') as csv_file:
            data = csv.reader(csv_file)
            database = [row for row in data]
        return database

    # Algorithm which scans longest sequence of STRs
    def scan_sequence(self, STR):
        # DNA sequence string is just a sequence of A C G T letters
        # 1) copy DNA sequence string
        sequence = self.sequence[:]
        # 2) replace all occurances with '#'
        sequence = re.sub(STR, "#", sequence)
        # 3) replace all letters with space
        sequence = re.sub("A|C|G|T", " ", sequence)
        # 4) split string, so we get a list of sequenced occurencies
        # ex. ['###','##','#','#####']
        sequence = sequence.split()

        # scan longest sequence in list
        if sequence == []:
            longest_sequence = 0
        else:
            longest_sequence = len(max(sequence, key=len))

        return longest_sequence

    # scans all STRs and returns ordered list of results
    def analyze(self):
        results = []
        for STR in self.STRs:
            longest_sequence = self.scan_sequence(STR)
            results.append(str(longest_sequence))
        return results

    # Determines who is owner of dna sample
    # by comparing results to database data
    def determine(self):
        analyze_results = self.analyze()
        result = ""

        for i in range(len(self.database) - 1):
            if self.database[i][1:] == analyze_results:
                result = self.database[i][0]

        if result == "":
            result = "No Match"

        return result


# create instance
x = DNA()
# print answer
print(x.DNA_sample_owner)