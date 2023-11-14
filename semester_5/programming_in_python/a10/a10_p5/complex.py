# JTMS-14
# a10_p5.py
# Faraz Ahmad
# fahmad@jacobs-university.de

class Complex(object):
    def __init__(self, real, imag):
        """Constructor to initialize a complex number."""
        self.real = real
        self.imag = imag

    def __add__(self, other):
        """Overloads the + operator to add two complex numbers."""
        return Complex(self.real + other.real, self.imag + other.imag)

    def __sub__(self, other):
        """Overloads the - operator to subtract two complex numbers."""
        return Complex(self.real - other.real, self.imag - other.imag)

    def __str__(self):
        """toString() for the complex number."""
        return f"{self.real} + {self.imag}i" if self.imag >= 0 else f"{self.real} - {-self.imag}i"
