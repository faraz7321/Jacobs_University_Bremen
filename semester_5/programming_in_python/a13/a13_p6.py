# JTMS-14
# a13_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de

import re   

file_name = input("Enter the name of the text file: ")
emails = []
print("Email addresses found:")
for email in emails:
    print(email)
        
pattern = r'\b[a-zA-Z][a-zA-Z]+@constructor\.university\b'
pattern = r"^\S+@\S+\.\S+$"
try:
    with open(file_name, 'r') as file:
        content = file.read()
        # Find all email addresses in the file
        emails = re.findall(pattern, content)
except FileNotFoundError:
    print(f"File '{file_name}' not found.")
