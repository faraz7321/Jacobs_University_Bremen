# JTMS-14
# a7_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

# function to calculate longest word from list
def longest_word(lst):
    longest = ""
    for word in lst:
        if len(word) > len(longest):
            longest = word
    return longest

input_str = input("Enter a string containing multiple words separated by space: ")

# creating list of words from the string
word_list = input_str.split(" ")

longest = longest_word(word_list)

print(f"The longest word is: {longest}")
print(f"The length of the longest word is: {len(longest)}")
