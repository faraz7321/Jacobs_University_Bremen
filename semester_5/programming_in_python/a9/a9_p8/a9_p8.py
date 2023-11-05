from article import Article
import datetime

n = int(input("Number of articles? "))
articles = []

# entering data
for _ in range(n):
    print(f"Entering data for article {_+1}:\n")
    
    title = input("Title: ")
    author = input("Author's name: ")
    pubDate = input("Publish Date YYYY-MM-DD format: ")
    year, month, day = map(int, pubDate.split('-'))
    page_count = int(input("Pages: "))
    price = float(input("Price: $"))

    article = Article(title, author, datetime.datetime(year, month, day), page_count, price)
    articles.append(article)

print("\nList of Articles:")
for article in articles:
    print(article)
    print()