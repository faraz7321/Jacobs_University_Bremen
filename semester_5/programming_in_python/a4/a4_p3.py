# JTMS-14
# a4_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# reading an uppercase char
while True:
    ch = input("Enter an uppercase character: ")
    if ch.isalpha() and ch.isupper():
        break
    else:
        print("Invalid input! Enter an uppercase character.")

# checking valid int input
while True:
    n = int(input("Enter an integer between 0 and 32: "))
    if 0 <= n <= 32:
        break
    else:
        print("Invalid input! Enter an integer between 0 and 32.")

# print
ascii_value = ord(ch)

for i in range(ascii_value, ascii_value + n + 1):
    print(chr(i), end=' ')

print()
