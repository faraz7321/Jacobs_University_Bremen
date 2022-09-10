{-
   A collection of reimplementations of elementary functions for
   working with lists. As an exercise, you may want to implement
   additional functions such as init, reverse, take, drop, null.
-}

-- |The length' function returns the length of a list.
length' :: [a] -> Int
length' [] = 0
length' (x:xs) = 1 + length' xs

-- |The head' function returns the first element of a list.
head' :: [a] -> a
head' [] = error "empty list"
head' (x:xs) = x

-- |The tail' function returns a list without the first element.
tail' :: [a] -> [a]
tail' [] = error "empty list"
tail' (x:xs) = xs

-- |The last' function returns the last element of a list.
last' :: [a] -> a
last' [] = error "empty list"
last' (x:[]) = x
last' (x:xs) = last' xs

-- |The map' function returns a list constructed by appling a function
-- |to all items in a list.
map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map' f xs

-- |The filter' function returns a list constructed from members of a
-- |list for which a predicate is true
filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (x:xs) = if p x then x : filter' p xs else filter' p xs
