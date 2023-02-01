from cs50 import get_string

text = get_string("Text:")
sentences =  text.count('.') + text.count('!') + text.count('?') + text.count('...') #counting all the pontuation types
words = text.count(' ') + 1 #getting the number of words
noalpha = 0
for i in range(0 , len(text)):
    if text[i].isalpha() == False:
        noalpha += 1
letters = len(text) - noalpha #the rest should be counted as letters
letters = letters * (100/words) #putting per 100 words
sentences = sentences * (100/words) #putting per 100 words
index = round((0.0588 * letters) - (0.296 * sentences) - 15.8) #the Colmena-Liau index
#printing results
if (index < 1):
    print("Before Grade 1")
elif (index > 16 ):
    print("Grade 16+")
else:
    print(f"Grade {index}")