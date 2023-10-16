# JTMS-14
# a6_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Function to count words in a line
def count_words(line):
    return len(line.split())

# Read the file name from the keyboard
file_name = input("Enter the name of the text file: ")

try:
    # Open the file and read it line by line
    with open(file_name, 'r') as f:
        line_number = 1  # Initialize line number
        for line in f:
            line = line.strip()  # Remove whitespaces
            word_count = count_words(line)
            print(f"Line {line_number} has {word_count} word(s).")
            line_number += 1  # Increment line number
except FileNotFoundError:
    print("File not found.")

