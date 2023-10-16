# JTMS-14
# a6_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Initialize sum variable to 0
total_sum = 0

# Read integer numbers from 'numbers.txt' and sum them
with open('numbers.txt', 'r') as f:
    for line in f:
        total_sum += int(line.strip())

# Print the sum
print("The sum of all numbers in 'numbers.txt' is:", total_sum)


