from article import Article
import datetime


# Create two article objects
article1 = Article("programming in c", "Faraz Ahmad", datetime.datetime.now(), 800, 29.99)
article2 = Article("Embedded Systems", "foronz",datetime.datetime(2020, 6, 13) , 3, 18.99)

# Print the details of the articles
print("Article 1:", article1)
print("\nArticle 2:", article2)
