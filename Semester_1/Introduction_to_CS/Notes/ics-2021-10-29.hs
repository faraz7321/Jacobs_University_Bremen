module Main (main) where

import Test.HUnit
import Data.Char

map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map' f xs

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f (x:xs)
  | f x       = x : filter' f xs
  | otherwise = filter' f xs

zip' :: [a] -> [b] -> [(a, b)]
zip' _ [] = []
zip' [] _ = []
zip' (x:xs) (y:ys) = (x,y) : zip' xs ys

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ _ [] = []
zipWith' _ [] _ = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

{-
  foldl (+) 0 [1..3]
     = foldl (+) (0 + 1) [2..3]
     = foldl (+) ((0 + 1) + 2) [3]
     = foldl (+) (((0 + 1) + 2) + 3) []
     = ((0 + 1) + 2) + 3 = 6

  foldl (+) 0 [1..3]
     = foldl (+) 1 [2..3]
     = foldl (+) 3 [3]
     = foldl (+) 6 []
     = 6
-}

foldl' :: (b -> a -> b) -> b -> [a] -> b
foldl' _ z [] = z
foldl' f z (x:xs) = foldl' f (f z x) xs

{-
  foldr (+) 0 [1..3]
     = 1 + (foldr (+) 0 [2..3])
     = 1 + (2 + (foldr (+) 0 [3]))
     = 1 + (2 + (3 + (foldr (+) 0 [])))
     = 1 + (2 + (3 + 0))
     = 6
-}

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ z [] = z
foldr' f z (x:xs) = f x (foldr' f z xs)

{- Lets implements map using folds. Here is an example:

   mapf succ [1..3]
      = foldr' ((:).succ) [] [1..3]
      = ((:).succ) 1 (foldr' ((:).succ) [] [2..3])
      = ((:).succ) 1 (((:).succ) 2 (foldr' ((:).succ) [] [3]))
      = ((:).succ) 1 (((:).succ) 2 (((:).succ) 3 (foldr' ((:).succ) [] [])))
      = ((:).succ) 1 (((:).succ) 2 (((:).succ) 3 []))
      = ((:).succ) 1 (((:).succ) 2 [4])
      = ((:).succ) 1 [3,4]
      = [2..4]
-}

mapf :: (a -> b) -> [a] -> [b]
mapf f xs = foldr' ((:) . f) [] xs

{- Functions like maximum of a list or minimum of a list are easy to
   implement using folds. Here is how you could define your own
   maximum' function.
-}

maximum' :: Ord a => [a] -> a
maximum' [] = error "empty list"
maximum' (x:xs) = foldl max' x xs
  where max' a b
          | a > b     = a
          | otherwise = b

mapTests = TestList [ map' even [1..4] ~?= [False,True,False,True]
                    , map' even [] ~?= []
                    , map' (*2) [] ~?= []
                    , map' (*2) [1..3] ~?= [2,4,6]
                    , map' ord "hello" ~?= [104,101,108,108,111]
                    ]

filterTests = TestList [ filter' even [1..10] ~?= [2,4,6,8,10]
                       , filter' even [] ~?= []
                       , filter' (\_ -> False) [1..10] ~?= []
                       , filter' (\_ -> False) "hello" ~?= []
                       ]
           
zipTests = TestList [ zip' [1..4] "hello" ~?= [(1,'h'),(2,'e'),(3,'l'),(4,'l')]
                    , zip' [1..4] [] ~?= ([] :: [(Int,Int)])
                    , zip' [] [1..4] ~?= ([] :: [(Int,Int)])
                    , zip' [] [] ~?= ([] :: [(Int,Int)])
                    , zip' "hello" [1..4] ~?= [('h',1),('e',2),('l',3),('l',4)]
                    , zip' [1..3] [4..6] ~?= [(1,4),(2,5),(3,6)]
                    ]

zipWithTests = TestList [ zipWith' (+) [1..3] [4..6] ~?= [5,7,9]
                        , zipWith' (\a b -> (a,b)) [1..3] [4..6] ~?= [(1,4),(2,5),(3,6)]
                        ]

foldlTests = TestList [ foldl' (+) 0 [1..10] ~?= sum [1..10]
                      , foldl' (*) 1 [1..10] ~?= product [1..10]
                      , foldl' max 1 [1..10] ~?= maximum [1..10]
                      , foldl' min 10 [1..10] ~?= minimum [1..10]
                      , foldl' (++) [] ["hel", "lo"] ~?= concat ["hel", "lo"]
                      ]

foldrTests = TestList [ foldr' (+) 0 [1..10] ~?= sum [1..10]
                      , foldr' (*) 1 [1..10] ~?= product [1..10]
                      , foldr' max 1 [1..10] ~?= maximum [1..10]
                      , foldr' min 10 [1..10] ~?= minimum [1..10]
                      , foldr' (++) [] ["hel", "lo"] ~?= concat ["hel", "lo"]
                      ]

mapfTests = TestList [ mapf (\x -> x * x) [1..3] ~?= [1,4,9]
                     , mapf succ [1..3] ~?= [2..4]
                     ]

allTests = TestList [ mapTests, filterTests, zipTests
                    , foldlTests, foldrTests, mapfTests ]

main = runTestTT allTests
