# JTMS-14
# a7_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

tuple_list = []

# Reading 7 tuples from the keyboard
for i in range(1, 8):
    input_str = input(f"Enter the components of tuple {i} separated by space: ")
    tup = tuple(input_str.split())
    tuple_list.append(tup)

# Remove empty tuples
filtered_list = [t for t in tuple_list if t]

print("List after removing empty tuples:", filtered_list)
