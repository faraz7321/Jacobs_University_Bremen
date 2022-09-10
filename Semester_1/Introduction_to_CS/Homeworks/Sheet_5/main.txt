--module Main (main) where

import Data.Char
import Data.List

dtob :: Int -> [Char]
dtob = reverse . map intToDigit . unfoldr (\x -> if x == 0 then Nothing else Just (rem x 2, div x 2))

btod :: [Char] -> Int
btod l = sum $ map (2 ^) $ elemIndices '1' $ reverse l
