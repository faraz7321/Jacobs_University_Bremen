# JTMS-14
# a11_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

while True:
    # take user input
    try:
        filename = input("Enter the file name: ")
        
        with open(filename, 'r') as file:
            content = file.read()

    except FileNotFoundError:
        print("the file does not exist")

    except PermissionError:
        print("you dont have permission to access this file")
        
    except Exception as e:
        print(f"unexpected error occurred: {e}")


