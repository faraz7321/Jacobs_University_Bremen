# JTMS-14
# a8_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def main():
    
    # Reading the start length, end length, and step size from the user
    start_length = float(input("Enter the start length in inches: "))
    end_length = float(input("Enter the end length in inches: "))
    step_size = float(input("Enter the step size: "))

    print("inch  cm")

    for length_in_inch in range(int(start_length * 10), int(end_length * 10) + 1, int(step_size * 10)):
        length_in_inch /= 10  # Convert back to float with 1 decimal place
        length_in_cm = length_in_inch * 2.54  # Convert to cm
        print(f"{length_in_inch:.1f}  {length_in_cm:.1f}")

if __name__ == "__main__":
    main()
