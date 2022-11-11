module Bankers (isSafe, isDead) where

import Data.List
import Debug.Trace

-- Calculate which processes can finish (ready). If none, return true
-- if alloc is empty and false otherwise. If processes can finish,
-- pick the first that finish and remove its row from the alloc and
-- max and recurse.

isSafe :: [Int] -> [[Int]] -> [[Int]] -> Bool
isSafe total max alloc
    | trace ("isSafe " ++ show total ++ " " ++ show max ++ " " ++ show alloc) False = undefined
    | null ready = null alloc
    | trace (" -> available " ++ show avail) False = undefined
    | trace (" -> finishing alloc=" ++ show (alloc !! idx)) False = undefined
    | otherwise  = isSafe total (del idx max) (del idx alloc)
    where
      avail = zipWith (-) total (map sum (transpose alloc))
      need  = zipWith (zipWith (-)) max alloc
      ready = filter (\r -> and (zipWith (<=) r avail)) need
      idx   = head $ elemIndices (head ready) need
      del n xs = delete (xs !! n) xs

isDead :: [Int] -> [[Int]] -> [[Int]] -> Bool
isDead total need alloc
    | trace ("isDead " ++ show total ++ " " ++ show need ++ " " ++ show alloc) False = undefined
    | null ready = (not . null) alloc
    | trace (" -> available " ++ show avail) False = undefined
    | trace (" -> finishing alloc=" ++ show (alloc !! idx)) False = undefined
    | otherwise  = isDead total (del idx need) (del idx alloc)
    where
      avail = zipWith (-) total (map sum (transpose alloc))
      ready = filter (\r -> and (zipWith (<=) r avail)) need
      idx   = head $ elemIndices (head ready) need
      del n xs = delete (xs !! n) xs
