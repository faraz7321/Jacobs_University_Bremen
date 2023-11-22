# JTMS-14
# a11_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de


# FormulaError Class
class FormulaError(Exception):
    """exception for errors in the formula input."""


while True:
    userInput = input("Enter a formula (or 'q' to exit): ")
    if userInput.lower() == 'q':
        break
    
    # split str into 3 parts
    try:
        parts = userInput.split()
        if len(parts) != 3:
            raise FormulaError("Invalid format: The formula must be of two \
                               numbers and an operator.")

        number1, operator, number2 = parts

        #convert to float
        try:
            number1 = float(number1)
            number2 = float(number2)
        except ValueError:
            raise FormulaError("Invalid number: The input must be of numerical \
                                values.")

        if operator not in ('+', '-'):
            raise FormulaError("Invalid operator: The operator must be either \
                                '+' or '-'.")

        # add operation
        if operator == '+':
            result = number1 + number2
        # subtract operation
        else:
            result = number1 - number2

        print("Result:", result)

    except FormulaError as e:
        print(e)



