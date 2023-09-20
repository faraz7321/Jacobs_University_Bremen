# JTMS-14
# a3_p5.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Main program
try:
    character = input("Enter a character: ")
    
    if len(character) != 1:
        print("Invalid input! Please enter a single character.")
    elif character.isalpha() and character.islower():
        print("The character is a lowercase alphabetic character.")
    else:
        print("The character is not a lowercase alphabetic character.")
        
except Exception as e:
    print(f"An error occurred: {e}")
