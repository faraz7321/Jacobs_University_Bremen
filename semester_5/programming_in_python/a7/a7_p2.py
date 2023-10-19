# JTMS-14
# a7_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

def translate(list_en):
    lexicon = {
        "merry": "god",
        "christmas": "jul",
        "and": "och",
        "happy": "gott",
        "new": "nytt",
        "year": "år"
    }
    
    list_sw = []
    for word in list_en:
        if word.lower() in lexicon:
            list_sw.append(lexicon[word.lower()])
        else:
            list_sw.append(word)  # Keep the original word if no translation is found
    
    return list_sw

# English greeting as a list
english_greeting = ["Merry", "Christmas", "and", "Happy", "New", "Year"]

# Translate to Swedish
swedish_greeting = translate(english_greeting)

# Join the list into a string and print the Swedish greeting
print(" ".join(swedish_greeting))
