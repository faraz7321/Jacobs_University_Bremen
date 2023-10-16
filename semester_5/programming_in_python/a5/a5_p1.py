# JTMS-14
# a5_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# convert volume (gallons and cups) to liters
def to_liter(gallon, cup):
    gallon_to_liter = 3.7854
    cup_to_liter = 0.2366
    total_liters = (gallon * gallon_to_liter) + (cup * cup_to_liter)
    return total_liters

# Read the number of gallons and cups from the user
gallon_input = float(input("Enter the number of gallons: "))
cup_input = float(input("Enter the number of cups: "))

total_liters = to_liter(gallon_input, cup_input)

print(f"The total volume is {total_liters} liters")
