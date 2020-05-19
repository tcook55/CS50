from cs50 import SQL
from sys import argv

db = SQL("sqlite:///students.db")

def main():

    #Check for correct house argument
    if argv[1] not in ("Slytherin", "Ravenclaw", "Hufflepuff", "Gryffindor"):
        print("Usage: roster.py Ravenclaw")

    #Query database
    lis = db.execute("Select * from students where house = ? order by last asc, first asc", argv[1])

    #Format print each row in query
    for i in lis:
        if i['middle'] is None:
            print("%s %s, born %s" % (i['first'], i['last'], i['birth']))
        else:
            print("%s %s %s, born %s" % (i['first'],i['middle'], i['last'], i['birth']))



main()