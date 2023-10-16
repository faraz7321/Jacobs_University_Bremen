# JTMS-14
# a4_p5.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Function to convert miles to kilometers
def convert(miles):
    return miles * 1.609344

miles = float(input("Enter the distance in miles: "))

kilometers = convert(miles)

print(f"{miles} miles is equal to {kilometers} kilometers.")
