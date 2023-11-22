# JTMS-14
# a11_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Super class 
class Vehicle:
    def __init__(self, max_speed, mileage):
        self.max_speed = max_speed
        self.mileage = mileage

    def __str__(self):
        return f"Vehicle with max speed of {self.max_speed} km/h and mileage of {self.mileage} km"

# sub class of Vehicle
class Bus(Vehicle):
    def __str__(self):
        return f"Bus with max speed of {self.max_speed} km/h and mileage of {self.mileage} km"

# objects of type Vehicle
vehicle1 = Vehicle(150, 20000)
vehicle2 = Vehicle(180, 30000)

# objects of type Bus
bus1 = Bus(100, 40000)
bus2 = Bus(90, 50000)

# Printing all objects
print(vehicle1)
print(vehicle2)
print(bus1)
print(bus2)
