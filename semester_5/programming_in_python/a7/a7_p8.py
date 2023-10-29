# JTMS-14
# a7_p8.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# Initialize an empty list to use as the stack
stack = []

while True:
    # Read command from the keyboard
    command = input()

    if command == 's':
        # Push a number onto the stack
        number = int(input())
        stack.append(number)
        print(f"Pushing {number}")

    elif command == 'p':
        # Pop a number from the stack
        if not stack:
            print("Stack underflow")
        else:
            popped = stack.pop()
            print(f"Popping element {popped}")

    elif command == 'e':
        # Empty the stack
        print("Emptying stack")
        while stack:
            popped = stack.pop()
            print(f"Popping element {popped}")

    elif command == 'q':
        # Quit the program
        print("Good Bye!")
        break
