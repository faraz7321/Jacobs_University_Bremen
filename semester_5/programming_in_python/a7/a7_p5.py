# JTMS-14
# a7_p5.py
# Faraz Ahmad
# fahmad@jacobs-university.de

int_list = []

# Reading integers from the keyboard until a negative integer is entered
while True:
    num = int(input("Enter an integer (negative integer to stop): "))
    if num < 0:
        break
    int_list.append(num)

# Convert the list to a tuple
input_tuple = tuple(int_list)

reversed_tuple = input_tuple[::-1]

print("Reversed tuple:", reversed_tuple)
