from networkx import johnson
from student import Student

student = Student('John', 3)
student.setScore(1, 100)
student.setScore(2, 95)
student.setScore(3, 50)

# Print the information about John
print("Student details before name change:")
print(student)

student.setName("Jack")

print("\nStudent details after name change:")
print(student)