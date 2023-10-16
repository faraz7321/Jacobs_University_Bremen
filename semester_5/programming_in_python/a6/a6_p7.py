# JTMS-14
# a6_p7.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Initialize an empty list to store the integers
input_list = []

# Read integers from the keyboard until zero is entered
while True:
    num = int(input("Enter a non-zero integer (or 0 to stop): "))
    if num == 0:
        break
    input_list.append(num)

# Calculate and print the maximum and minimum values
if len(input_list) > 0:
    max_val = max(input_list)
    min_val = min(input_list)
    print(f"The maximum value in the list is: {max_val}")
    print(f"The minimum value in the list is: {min_val}")
else:
    print("No values were entered.")

