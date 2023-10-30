# JTMS-14
# mod_conversion.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def in2cm_table_html(start_length, end_length, step_size, output_to_screen):
    html_content = "<html><head><title>Conversion Table</title></head><body>"
    html_content += "<table border='1'><tr><th>inch</th><th>cm</th><th>m</th><th>km</th></tr>"
    
    for length_in_inch in range(int(start_length * 10), int(end_length * 10) + 1, int(step_size * 10)):
        length_in_inch /= 10  # Convert back to float with 1 decimal place
        length_in_cm = length_in_inch * 2.54  # Convert to cm
        length_in_m = length_in_cm / 100  # Convert to m
        length_in_km = length_in_m / 1000  # Convert to km

        html_content += f"<tr><td>{length_in_inch:.1f}</td><td>{length_in_cm:.1f}</td><td>{length_in_m:.4f}</td><td>{length_in_km:.7f}</td></tr>"

    html_content += "</table></body></html>"

    if output_to_screen:
        print(html_content)
    else:
        with open("in2cm.html", "w") as file:
            file.write(html_content)
