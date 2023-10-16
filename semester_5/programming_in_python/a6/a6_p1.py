# JTMS-14
# a6_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Reading the two characters from 'input.txt'
with open('input.txt', 'r') as f:
    chars = f.read(2)  # Read only two characters

if len(chars) != 2:
    print("The file should contain exactly two characters.")
else:
    # Calculating the product of the ASCII codes of the two characters
    ascii_product = ord(chars[0]) * ord(chars[1])

    # Writing the result to 'output.txt'
    with open('output.txt', 'w') as f:
        f.write(str(ascii_product))