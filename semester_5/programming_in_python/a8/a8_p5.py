# JTMS-14
# a8_p5.py
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

# Example usage of the queue and its functions
enqueue(10)
enqueue(20)
enqueue(30)
enqueue(40)
enqueue(50)

printq()  # current queue: [10, 20, 30, 40, 50]

element = dequeue()
print(f"Dequeued element: {element}")  # dequeued element: 10

printq()  # current queue: [20, 30, 40, 50]

element = dequeue()
print(f"Dequeued element: {element}")  # dequeued element: 20

printq()  # current queue: [30, 40, 50]
