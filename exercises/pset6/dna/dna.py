import sys
import csv
def main():
    if len(sys.argv) != 3:  #only accept the correct input
        print('Usage: "python dna.py data.csv sequence.txt" ')
        return False
    with open(f'{sys.argv[1]}','r') as database:    #opening files
        database_csv = csv.reader(database, delimiter=",")
        with open(f'{sys.argv[2]}','r') as sequence:
            sequence_txt = list(sequence.read())    #converting the txt in a list with one caracter in each position
            for i, line in enumerate(database_csv):
                if (i == 0):
                    points = []    #this variable will store the number of consecutive STRs
                    points = [0 for i in range(len(line))]      #starting it with the "correct" size
                    for j in range(1,len(line)):    #iterating to one STRs at a time
                        temp = 0
                        for k in range(0,len(sequence_txt)):    #comparing that one STR with all of the txt file
                            while (list(line[j]) == sequence_txt[k : k + len(line[j])]):
                                temp += 1
                                if temp > points[j]:    #making the substitution if this current count is higher than the previous one
                                    points[j] = temp
                                k += len(line[j])   #navegatin through the list
                            temp = 0
                if len(points)== len(line):     #removing the first and empty space on the list and converting it to string, so the comparison works properly
                    del points[0]
                    for i in range(len(points)):
                        points[i] = str(points[i])
                if points == line[1:len(line)]:     #printing the result
                    print(line[0])
                    return 0
            print("No match")
            return 0
if __name__== "__main__" :
    main()