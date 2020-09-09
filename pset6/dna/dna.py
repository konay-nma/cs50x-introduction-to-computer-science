from sys import argv
import csv

# check command-line arguments, expect 3 including dna.py
if (len(argv) != 3):
    print('Usage: python dna.py data.csv sequence.txt')

with open(argv[1], 'r') as database:  # read database
    data_lines = csv.reader(database)  # read line-by-line, store in data_lines
    data = [row for row in data_lines]  # convert to list of lists, store in data

with open(argv[2], 'r') as sequences:
    dna = sequences.read()  # read sequence data, store in string dna

counts = []  # list to store counts of the longest run of consecutive repeats of each STR

for i in range(1, len(data[0])):  # loop through all STR
    count = 1
    string = data[0][i]  # assign each STR to a string
    while string * count in dna:  # if find 1 string, then try to find string*2, and so on
        count += 1
    counts.append(str(count - 1))  # should be decreased by 1 as initialized to 1. int to str

for j in range(1, len(data)):  # loop through all rows in database
    if data[j][1:len(data[0])] == counts:  # compare only numebrs in each row to counts
        print(data[j][0])  # print corresponding name
        exit(0)
print('No Match')