# JTMS-14
# a13_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

import requests

def fetch_weather_data(month):
    # Construct the URL with the given month
    url = f"https://grader.eecs.jacobs-university.de/courses/350112/python/csv/exp2008{month:02}.csv"
    response = requests.get(url)

    if response.status_code == 200:
        # writing the data to a local file
        with open('./wdata1.csv', 'w') as file:
            file.write(response.text)
        print("Weather data downloaded.")
    else:
        print("Failed.")

def main():
    # Input from the user
    month = int(input("Enter the month number (01-12): "))
    fetch_weather_data(month)

main()