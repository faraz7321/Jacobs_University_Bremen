# JTMS-14
# a13_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

import csv
from datetime import datetime

input_file = 'wdata1.csv'
output_file = 'wdata2.csv'
day = 11
month = 3


with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
    reader = csv.DictReader(infile)
    writer = csv.writer(outfile)
    writer.writerow(['Date and Time',
                     'Temperature', 
                     'Humidity', 
                     'Wind', 
                     'Direction'])

    for row in reader:
        date = datetime.strptime(row['Datum'], '%y-%m-%d %H:%M')
        if date.day == day and date.month == month:
            writer.writerow([
                date.strftime('%y-%m-%d %H:%M'),
                row['Temperatur'],
                row['Feuchte'],
                row['Wind'],
                row['Richtung']
            ])

