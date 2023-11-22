# JTMS-14
# a11_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# ZeroDivisionError
try:
    number = 10 / 0
except ZeroDivisionError as e:
    print("Caught ZeroDivisionError:", e)

# IndexError
try:
    intlist = [1, 2, 3]
    print(intlist[3])
except IndexError as e:
    print("Caught IndexError:", e)

#  KeyError
try:
    dict = {"apple": 1, "banana": 2}
    print(dict["carrot"])
except KeyError as e:
    print("Caught KeyError:", e)