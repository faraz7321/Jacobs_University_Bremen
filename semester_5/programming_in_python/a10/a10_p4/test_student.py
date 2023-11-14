# JTMS-14
# a10_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from student import Student
import random

# Create 10 students
students = [
    Student("Faraz Ahmad", 3),
    Student("John Smith", 13),
    Student("Muaaz Rajput", 5),
    Student("Hello Abc", 213),
    Student("Bye Bye", 5),
    Student("Muhammad bin Salman", 4),
    Student("Imran Khan", 234),
    Student("Bruce Lee", 67),
    Student("Walter White", 67),
    Student("Tony Clark", 9)
]

# Shuffle the list
random.shuffle(students)
print("Shuffled Students:")
for student in students:
    print(student.getName())

# Sort the list in descending order
students.sort(reverse=True)
print("\nStudents in Descending Order:")
for student in students:
    print(student.getName())
