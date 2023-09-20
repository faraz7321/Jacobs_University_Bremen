# JTMS-14
# a3_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# 1. Reads a string and an integer value and multiplies them
try:
    string1 = input("Enter a string: ")
    int1 = int(input("Enter an integer: "))
    result1 = string1 * int1
    print(f"Result 1: {result1}")
    # Strings can be multiplied by integers, replicating the string.
except Exception as e:
    print(f"Error in case 1: {e}")

# 2. Reads two integer values without converting them to int. Adds these numbers.
try:
    int_str1 = input("Enter an integer (as string): ")
    int_str2 = input("Enter another integer (as string): ")
    result2 = int_str1 + int_str2
    print(f"Result 2: {result2}")
    # The '+' operator concatenates the two strings, instead of addition.
except Exception as e:
    print(f"Error in case 2: {e}")

# 3. Reads a string and a floating point value and multiplies them
try:
    string3 = input("Enter a string: ")
    float3 = float(input("Enter a float: "))
    # result3 = string3 * float3  # This line will cause an error if uncommented
    # Strings can't be multiplied by floats, result in a TypeError.
    # print(f"Result 3: {result3}")
except Exception as e:
    print(f"Error in case 3: {e}")