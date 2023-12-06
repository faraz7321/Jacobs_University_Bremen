# JTMS-14
# a13_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de

import matplotlib.pyplot as plt
import numpy as np

# Generate data
x = np.arange(-20, 21, 1)
y = x * 3

# exporting data to a file
with open('data.dat', 'w') as file:
    for x_val, y_val in zip(x, y):
        file.write(f"{x_val} {y_val}\n")

# Plotting
plt.plot(x, y, marker='o')
plt.title('Plot of x and x*3')
plt.xlabel('x')
plt.ylabel('x*3')
plt.grid(True)

plt.savefig('plot.pdf')
