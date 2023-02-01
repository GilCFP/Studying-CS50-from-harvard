import sys
with open(f'{sys.argv[1]}','r') as sequence:
    text = sequence.read()
    print(text)