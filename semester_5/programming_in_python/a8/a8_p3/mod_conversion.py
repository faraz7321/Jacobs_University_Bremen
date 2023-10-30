# JTMS-14
# mod_conversion.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def in2cm_table(start_length, end_length, step_size):
    with open("table.txt", "w") as file:
        # Writing the header of the table to the file
        file.write(f"{'inch':>5} {'cm':>7} {'m':>12} {'km':>18}\n")

        # Generating and write the table to the file
        for length_in_inch in range(int(start_length * 10), int(end_length * 10) + 1, int(step_size * 10)):
            length_in_inch /= 10  # Convert back to float with 1 decimal place
            length_in_cm = length_in_inch * 2.54  # Convert to cm
            length_in_m = length_in_cm / 100  # Convert to m
            length_in_km = length_in_m / 1000  # Convert to km

            file.write(f"{length_in_inch:>5.1f} {length_in_cm:>7.1f} {length_in_m:>12.4f} {length_in_km:>18.7f}\n")
