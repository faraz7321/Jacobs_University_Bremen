# JTMS-14
# a6_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Define the histogram function
def histogram(lst):
    for num in lst:
        print('*' * num)

# Read the number of elements n
n = int(input("Enter the number of elements in the list: "))

# Read n integer numbers from the keyboard to populate the list
input_list = []
for i in range(n):
    num = int(input(f"Enter element {i+1}: "))
    input_list.append(num)

# Call the histogram function
histogram(input_list)


