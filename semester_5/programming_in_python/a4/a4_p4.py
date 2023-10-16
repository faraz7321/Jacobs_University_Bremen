# JTMS-14
# a4_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# list to hold the integers
numbers = []

# sum and count of numbers
total_sum = 0
count = 0

# get up to 10 integers
for i in range(1, 11):  # 1 to 10 inclusive
    num = int(input(f"Enter integer {i} (or -9 to stop): "))
    
    if num == -9:
        break
    
    numbers.append(num)
    total_sum += num
    count += 1

# making sure at least one number was entered
if count == 0:
    print("No numbers entered!")
else:
    # print the average
    average = total_sum / count
    print(f"The average is {average}")
