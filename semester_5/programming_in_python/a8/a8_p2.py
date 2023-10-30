# JTMS-14
# a8_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def main():

    # Reading the start length, end length, and step size from the user
    start_length = float(input("Enter the start length in inches: "))
    end_length = float(input("Enter the end length in inches: "))
    step_size = float(input("Enter the step size: "))

    # Opening the file for writing
    with open("table.txt", "w") as file:
        file.write(f"{'inch':>5} {'cm':>7} {'m':>12} {'km':>18}\n")

        # Generating and write the table to the file
        for length_in_inch in range(int(start_length * 10), int(end_length * 10) + 1, int(step_size * 10)):
            length_in_inch /= 10  
            length_in_cm = length_in_inch * 2.54 
            length_in_m = length_in_cm / 100  
            length_in_km = length_in_m / 1000 

            file.write(f"{length_in_inch:>5.1f} {length_in_cm:>7.1f} {length_in_m:>12.4f} {length_in_km:>18.7f}\n")

if __name__ == "__main__":
    main()
