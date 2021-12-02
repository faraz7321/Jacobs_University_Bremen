{-

  Given a list of numbers, calculate their sum.

  A list is either an empty list ([]) or it is an element prepended to
  a list (and the operator for prepending is :).

  [1,2,3] = 1 : 2 : 3 : []

  The sum of a list of numbers is defined to be

   0           for the empty list []
   h + (sum t) for a list with the head element h followed by a tail (h:t)

-}

sum' :: [Integer] -> Integer
sum' xs = if null xs then 0 else (head xs) + (sum' (tail xs))

sum'' :: Num p => [p] -> p
sum'' [] = 0
sum'' (h:t) = h + sum'' t

{-
   Evaluation of sum'' [1..5]:

   sum'' [1..5] = 1 + sum'' [2..5]
                = 1 + 2 + sum'' [3..5]
                = 1 + 2 + 3 + sum'' [4..5]
                = 1 + 2 + 3 + 4 + sum'' [5]
                = 1 + 2 + 3 + 4 + 5 + sum'' []
                = 1 + 2 + 3 + 4 + 5 + 0
                = 15
-}

{-
   Write a function length' that calculates the length of a list.
-}

length' :: [a] -> Integer
length' [] = 0
length' (_:xs) = 1 + length' xs

