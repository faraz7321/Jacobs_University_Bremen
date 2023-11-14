# JTMS-14
# a10_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from student import Student

student1 = Student("John Doe", 3)
student2 = Student("Jane Smith", 3)
student3 = Student("John Doe", 3)

print(f"{student1.getName()} == {student2.getName()}: {student1 == student2}")
print(f"{student1.getName()} != {student3.getName()}: {student1 != student3}")
print(f"{student1.getName()} < {student2.getName()}: {student1 < student2}")
print(f"{student1.getName()} <= {student3.getName()}: {student1 <= student3}")
print(f"{student2.getName()} > {student1.getName()}: {student2 > student1}")
print(f"{student2.getName()} >= {student3.getName()}: {student2 >= student3}")