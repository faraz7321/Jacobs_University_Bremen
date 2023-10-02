# JTMS-14
# a4_p7.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Function to print the frame
def print_frame(n, m, c):
    for i in range(n):
        for j in range(m):
            if i == 0 or i == n - 1 or j == 0 or j == m - 1:
                print(c, end='')
            else:
                print(' ', end='')
        print()

# Get integer and character input from the user
n = int(input("Enter the number of rows (n): "))
m = int(input("Enter the number of columns (m): "))
c = input("Enter a character (c): ")

print_frame(n, m, c)
