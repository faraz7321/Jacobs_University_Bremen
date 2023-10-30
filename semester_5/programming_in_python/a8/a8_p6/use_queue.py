# JTMS-14
# use_queue.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from module_queue import enqueue, dequeue, printq

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
