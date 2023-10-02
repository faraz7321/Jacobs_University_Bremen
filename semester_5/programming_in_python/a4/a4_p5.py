# JTMS-14
# a4_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Function to print the rectangle
def print_rectangle(n, m, c):
    for i in range(n):
        for j in range(m):
            print(c, end='')
        print()

# Getting integer and character input from the user
n = int(input("Enter the number of rows (n): "))
m = int(input("Enter the number of columns (m): "))
c = input("Enter a character (c): ")

print_rectangle(n, m, c)
