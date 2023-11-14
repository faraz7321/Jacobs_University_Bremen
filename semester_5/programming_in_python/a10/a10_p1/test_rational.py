# JTMS-14
# a10_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from rational import Rational

r1 = Rational(1, 2)
r2 = Rational(2, 3)
r3 = Rational(2, 4)

print(f"{r1} != {r2}: {r1 != r2}")
print(f"{r1} <= {r2}: {r1 <= r2}")
print(f"{r1} > {r3}: {r1 > r3}")
print(f"{r1} >= {r3}: {r1 >= r3}")