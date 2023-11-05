from student import Student


jenny = Student("Jenny", 2)
steve = Student("Steve", 2)
celine = Student("Celine", 2)
students = [jenny, steve, celine]
for student in students:
    student.setScore(1, 95)
    student.setScore(2, 90)

for student in students:
    print(student)


