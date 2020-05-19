from cs50 import SQL
from sys import argv
import csv

db = SQL("sqlite:///students.db")

def main():
    #Check for 1 argument
    if len(argv) > 2:
        print("Usage: import.py characters.csv")
        return

    #Open provided csv file
    with open(argv[1], "r") as file:
        #Create CSV dictionary reader
        reader = csv.DictReader(file)
        for row in reader:
            #Find first, middle, and last name
            name = parse(row['name'])

            #Determine what values to give based on the presence of a middle name or not
            if len(name) != 3:
                sql = "INSERT INTO students (first, last, house, birth) VALUES (%s, %s, %s, %s)"
                val = (name[0], name[1], row['house'], row['birth'])
            else:
                sql = "INSERT INTO students (first, middle, last, house, birth) VALUES (%s, %s, %s, %s, %s)"
                val = (name[0], name[1], name[2], row['house'], row['birth'])

            db.execute(sql, val)



#Find the first, middle, and last name in given string and return as list
def parse(name):
    split = []
    marker = 0
    ctr = 0

    while ctr <= len(name):
        if ctr == len(name):
            split.append(name[marker:ctr])
            break
        if name[ctr] == " ":
            split.append(name[marker:ctr])
            marker = ctr + 1
        ctr += 1

    return(split)


main()