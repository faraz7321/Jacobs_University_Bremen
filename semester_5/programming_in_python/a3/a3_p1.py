# JTMS-14
# a3_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Function to convert minutes to hours and minutes
def convert_to_minutes(minutes):
    hours = minutes // 60
    remaining_minutes = minutes % 60
    
    return hours, remaining_minutes

# main 
try:
    input = int(input("Enter the time in minutes: "))
    hours, minutes = convert_to_minutes(input)
    print(f"{input} minutes is equal to {hours} hours and {minutes} minutes.")
except ValueError:
    print("Invalid input! Please enter an integer.")
