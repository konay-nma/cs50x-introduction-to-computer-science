from cs50 import get_string

letters = 0
words = 0
sentences = 0
string_text = get_string("Text: ")
print(string_text.lower())

for i in range(len(string_text)):
    char = string_text[i]
    if (char.isalpha()):
        letters += 1
    elif (char == " "):
        words += 1
    elif (char == '.' or char == '?' or char == '!'):
        sentences += 1

words += 1
L = letters / words * 100
S = sentences / words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
print(letters, words, sentences, index)
if (index < 16 and index >= 0):
    print(f"Grade {index}")
elif (index >= 16):
    print(f"Grade 16+")
else:
    print("Before Grade 1")