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

    def __mul__(self, other):
        """Overloads the * operator to multiply two complex numbers."""
        real = self.real * other.real - self.imag * other.imag
        imag = self.imag * other.real + self.real * other.imag
        return Complex(real, imag)

    def __truediv__(self, other):
        """Overloads the / operator to divide two complex numbers."""
        divisor = other.real**2 + other.imag**2
        real = (self.real * other.real + self.imag * other.imag) / divisor
        imag = (self.imag * other.real - self.real * other.imag) / divisor
        return Complex(real, imag)

    def __eq__(self, other):
        """Checks if two complex numbers are equal."""
        return self.real == other.real and self.imag == other.imag

    def __ne__(self, other):
        """Checks if two complex numbers are not equal."""
        return not self.__eq__(other)