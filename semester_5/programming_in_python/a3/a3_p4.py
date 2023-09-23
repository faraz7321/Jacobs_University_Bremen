# JTMS-14
# a3_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# main 
try:
    input = int(input("Enter an integer value: "))
    
    if input % 11 == 0:
        print("The number is divisible by 11")
    else:
        print("The number is not divisible by 11")

except ValueError:
    print("Invalid input! Please enter an integer.")
