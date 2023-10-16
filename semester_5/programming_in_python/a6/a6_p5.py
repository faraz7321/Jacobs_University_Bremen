# JTMS-14
# a6_p5.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Function to add val to all elements in the list
def add(lst, val):
    return [x + val for x in lst]

# Function to multiply all elements in the list by val
def multiply(lst, val):
    return [x * val for x in lst]

# Read the number of elements n
n = int(input("Enter the number of elements in the list: "))

# Read n float numbers from the keyboard
original_list = []
for i in range(n):
    num = float(input(f"Enter element {i+1}: "))
    original_list.append(num)

# Use the add and multiply functions
added_list = add(original_list, 1.5)
multiplied_list = multiply(original_list, 5)

# Print the original and modified lists
print("Original list:", original_list)
print("List after adding 1.5:", added_list)
print("List after multiplying by 5:", multiplied_list)

