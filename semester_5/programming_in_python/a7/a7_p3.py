# JTMS-14
# a7_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def scalar_product(v, w):
    return sum(v_i * w_i for v_i, w_i in zip(v, w))

# get  the integer n
n = int(input("Enter the integer n for the length of the tuples: "))

# get and convert the tuples v and w
v = tuple(map(float, input(f"Enter {n} components of tuple v separated by space: ").split()))
w = tuple(map(float, input(f"Enter {n} components of tuple w separated by space: ").split()))

result = scalar_product(v, w)

# smallest and largest components and their positions
min_v, max_v = min(v), max(v)
min_w, max_w = min(w), max(w)
min_v_pos, max_v_pos = v.index(min_v), v.index(max_v)
min_w_pos, max_w_pos = w.index(min_w), w.index(max_w)

print(f"The scalar product of v and w is: {result}")
print(f"The smallest component of v is {min_v} at position {min_v_pos+1}")
print(f"The largest component of v is {max_v} at position {max_v_pos+1}")
print(f"The smallest component of w is {min_w} at position {min_w_pos+1}")
print(f"The largest component of w is {max_w} at position {max_w_pos+1}")
