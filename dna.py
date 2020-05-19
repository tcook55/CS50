from sys import argv
import csv

def main():

    #Check for correct number of inputs
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    #open and read text file
    file = open(argv[2], "r")
    f_con = file.read()

    #Open database and load unique SRT's into dictionary
    sfile = open(argv[1])
    reader = csv.reader(sfile)
    headers = next(reader, None)
    SRT = {}
    i = 1
    while i < len(headers):
        SRT[headers[i]] = 0
        i += 1
    sfile.close()

    #Parse the text file searching for SRT sequences
    counts = parsed(SRT, f_con)


    for i in counts:
        print(f"{i} {counts[i]}")

    result = match(argv[1], SRT)
    print(result)



    sfile.close()
    file.close()


#Function to count the longest sequence of each SRT
def parsed(srt, txt):
    i = 0
    while i < len(txt):
        for j in srt.keys():
            if txt[i:i+len(j)] == j:
                temp = 1
                flag = True
                i += len(j)
                while flag == True:
                    if txt[i:i+len(j)] == j:
                        temp += 1
                        i += len(j)
                    else:
                        if temp > srt[j]:
                            srt[j] = temp
                        flag = False
        i += 1
    return srt


def match(arg, SRT):
    matches = 0
    with open(arg, "r") as sfile:
        reader = csv.DictReader(sfile)
        for row in reader:
            for i in SRT:
                if int(row[i]) == SRT[i]:
                    matches += 1
                else:
                    break
                if matches == len(SRT):
                    return(row['name'])
    return("No matches")

main()