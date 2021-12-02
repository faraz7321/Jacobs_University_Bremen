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

foldl' :: (b -> a -> b) -> b -> [a] -> b
foldl' = foldl

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' = foldr

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
                      ]

foldrTests = TestList [ foldr' (+) 0 [1..10] ~?= sum [1..10]
                      , foldr' (*) 1 [1..10] ~?= product [1..10]
                      ]

allTests = TestList [ mapTests, filterTests, zipTests, foldlTests, foldrTests ]

main = runTestTT allTests
