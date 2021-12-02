module Main (main) where

import Test.HUnit
import Data.List

msort :: Ord a => [a] -> [a]
msort [] = []
msort [x] = [x]
msort (x:xs) = msort smaller ++ [x] ++ msort bigger
  where (smaller, bigger) = partition (< x) xs

qsort :: Ord a => (a -> a -> Ordering) -> [a] -> [a]
qsort _ [] = []
qsort _ [x] = [x]
qsort c (x:xs) = qsort c smaller ++ [x] ++ qsort c bigger
  where (smaller, bigger) = partition ((== GT).c x) xs
  
msortTests = TestList [ msort [5,1,3,8,7,2,6] ~?= [1,2,3,5,6,7,8]
                      , msort [1,2,3,4,5] ~?= [1,2,3,4,5]
                      , msort [5,4,3,2,1] ~?= [1,2,3,4,5]
                      , msort [1,2,1,2,1] ~?= [1,1,1,2,2]
                      , msort [] ~?= ([] :: [Int])
                      , msort [1] ~?= [1]
                      , msort "hello" ~?= "ehllo"
                      ]
                 
qsortTests = TestList [ qsort compare [5,1,3,8,7,2,6] ~?= [1,2,3,5,6,7,8]
                      , qsort compare [1,2,3,4,5] ~?= [1,2,3,4,5]
                      , qsort compare [5,4,3,2,1] ~?= [1,2,3,4,5]
                      , qsort compare [1,2,1,2,1] ~?= [1,1,1,2,2]
                      , qsort compare [] ~?= ([] :: [Int])
                      , qsort compare [1] ~?= [1]
                      , qsort compare "hello" ~?= "ehllo"
                      , qsort (flip compare) "hello" ~?= "ollhe"
                      ]
                 
main = runTestTT $ TestList [msortTests, qsortTests]
