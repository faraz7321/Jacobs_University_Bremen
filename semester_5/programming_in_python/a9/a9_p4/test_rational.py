from rational import Rational

# Input for the first rational number
input_str = input("Enter the first rational number (e.g., 1/2): ")
numerator1, denominator1 = map(int, input_str.split('/'))

# Input for the second rational number
input_str = input("Enter the second rational number: ")
numerator2, denominator2 = map(int, input_str.split('/'))

# Creating two rational number objects
rational1 = Rational(numerator1, denominator1)
rational2 = Rational(numerator2, denominator2)

# Print the rational numbers
print("First rational number", rational1)
print("Second rational number is:", rational2)

# Print the sum of the two rational numbers
sum_rational = rational1 + rational2
print("\nThe sum of the two rational numbers is:", sum_rational)