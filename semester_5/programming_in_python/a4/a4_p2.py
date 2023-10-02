# JTMS-14
# a4_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

ch = input("Enter an uppercase character: ")
n = int(input("Enter an integer: "))

ascii_value = ord(ch)

for i in range(ascii_value, ascii_value + n + 1):
    print(chr(i), end=' ')

print()
