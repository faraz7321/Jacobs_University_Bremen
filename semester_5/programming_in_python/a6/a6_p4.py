# JTMS-14
# a6_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Read the name of the text file from the keyboard
file_name = input("Enter the name of the text file: ")

try:
    # Read the content of the specified file
    with open(file_name, 'r') as infile:
        content = infile.read()

    # Write the content into 'copy.txt'
    with open('copy.txt', 'w') as outfile:
        outfile.write(content)

    print("File has been successfully copied to 'copy.txt'.")
except FileNotFoundError:
    print("File not found.")
