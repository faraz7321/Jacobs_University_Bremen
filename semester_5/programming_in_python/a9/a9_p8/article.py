# File: article.py


class Article(object):
    """Represents an article"""

    def __init__(self, title, author, pubDate, page_count, price):
        """Initializes an article with title, author, pubDate, page count, and price."""
        self._title = title
        self._author = author
        self._pubDate = pubDate
        self._page_count = page_count
        self._price = price

    # Setters
    def setTitle(self, title):
        self._title = title

    def setAuthor(self, author):
        self._author = author

    def setPubDate(self, pubDate):
        self._pubDate = pubDate

    def setPageCount(self, page_count):
        self._page_count = page_count

    def setPrice(self, price):
        self._price = price

    # Getters
    def getTitle(self):
        return self._title

    def getAuthor(self):
        return self._author

    def getPubDate(self):
        return self._pubDate

    def getPageCount(self):
        return self._page_count

    def getPrice(self):
        return self._price

    def __str__(self):
        return (f"Title: {self._title}\n"
                f"Author: {self._author}\n"
                f"Publish Date: {self._pubDate}\n"
                f"Page Count: {self._page_count}\n"
                f"Price: ${self._price:.2f}")

