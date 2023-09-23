# JTMS-14
# a3_p7.py
# Faraz Ahmad
# fahmad@jacobs-university.de

try:
    n = int(input("Enter an integer greater than or equal to 1: "))
    
    if n < 1:
        print("Please enter an integer greater than or equal to 1.")
    else:
        i = 1
        while i <= n:
            if i == 1:
                print(f"{i} minute = {i * 60} seconds")  # Singular case
            else:
                print(f"{i} minutes = {i * 60} seconds")  # Plural case
            i += 1

except ValueError:
    print("Invalid input! Please enter an integer.")
