# JTMS-14
# a8_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from mod_conversion import in2cm_table

def main():
    # Read the start length, end length, and step size from the user
    start_length = float(input("Enter the start length in inches: "))
    end_length = float(input("Enter the end length in inches: "))
    step_size = float(input("Enter the step size: "))
    
    # Generate the conversion table
    in2cm_table(start_length, end_length, step_size)

if __name__ == "__main__":
    main()
