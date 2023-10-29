# JTMS-14
# a7_p7.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Creating an example dictionary
example_dict = {
    'apple': 1,
    'banana': 2,
    'mango': 3,
    'orange': 4
}

# Reading key
key_to_check = input("Enter a key to check if it's present in the dictionary: ")

# Checking if the key is present in the dictionary
if key_to_check in example_dict:
    print(f"The key '{key_to_check}' is present in the dictionary.")
else:
    print(f"The key '{key_to_check}' is not present in the dictionary.")
