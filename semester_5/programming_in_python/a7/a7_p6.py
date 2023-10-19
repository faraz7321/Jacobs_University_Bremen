# JTMS-14
# a7_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def find_min_key(d):
    min_key = min(d, key=d.get)
    return min_key

# Example dictionary
sampleDict = {'Physics': 82, 'Math': 85, 'History': 75, 'Management': 70, 'Chemistry': 72}

min_key = find_min_key(sampleDict)

print(f"The key corresponding to the minimum value is: {min_key}")
