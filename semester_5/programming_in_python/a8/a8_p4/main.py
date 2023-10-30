# JTMS-14
# a8_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from mod_conversion import in2cm_table_html

def main():
    # Read the start length, end length, and step size from the user
    start_length = float(input("Enter the start length in inches: "))
    end_length = float(input("Enter the end length in inches: "))
    step_size = float(input("Enter the step size: "))
    
    #  where to output the table
    output_choice = input("Enter 's' to print to screen, any other key to print to file: ")
    output_to_screen = output_choice.lower() == 's'

    # Generate the conversion table
    in2cm_table_html(start_length, end_length, step_size, output_to_screen)

if __name__ == "__main__":
    main()
