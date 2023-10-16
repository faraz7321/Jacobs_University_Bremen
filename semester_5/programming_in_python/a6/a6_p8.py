# JTMS-14
# a6_p8.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Define the overlapping function
def overlapping(list1, list2):
    for item1 in list1:
        if item1 in list2:
            return True
    return False

# Function to read list from keyboard
def read_list():
    lst = []
    while True:
        num = int(input("Enter a positive integer or zero (or a negative number to stop): "))
        if num < 0:
            break
        lst.append(num)
    return lst

# Read two lists from the keyboard
list1 = read_list()
list2 = read_list()

# Call the overlapping function and print the result
if overlapping(list1, list2):
    print("The two lists are overlapping.")
else:
    print("The two lists are not overlapping.")

