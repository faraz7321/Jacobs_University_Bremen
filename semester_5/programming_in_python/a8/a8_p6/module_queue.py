# JTMS-14
# a8_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Initialize an empty queue as a list
queue = []

# add an element at the end of the queue
def enqueue(element):
    global queue
    queue.append(element)

# remove an element from the front of the queue
def dequeue():
    global queue
    if len(queue) == 0:
        print("Queue is empty. Cannot dequeue.")
        return None
    return queue.pop(0)

# print the content of the queue
def printq():
    global queue
    print("Current queue:", queue)
