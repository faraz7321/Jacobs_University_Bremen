{- |
   Module: bankerstest.hs

Unit tests for the Bankers module.
-}

module Main where

import Bankers
import Test.HUnit

s1 = (total, max, alloc)
    where total = [6,8,10,12]
          max   = [ [3,1,2,5],
                    [3,2,5,7],
                    [2,6,3,1],
                    [5,4,9,2],
                    [1,3,8,9] ]
          alloc = [ [0,0,2,1],
                    [1,0,1,2],
                    [1,2,1,1],
                    [3,4,0,0],
                    [0,0,4,2] ]

s2 = (total, max, alloc)
    where total = [6,8,10,12]
          max   = [ [3,1,2,5],
                    [3,2,5,7],
                    [2,6,3,1],
                    [5,4,9,2],
                    [1,3,8,9] ]
          alloc = [ [1,0,2,1],
                    [1,1,2,5],
                    [1,2,3,1],
                    [1,1,1,2],
                    [1,0,2,2] ]

s3 = (total, need, alloc)
     where total = [1,2,1,3]
           need  = [ [1,0,0,0],
                     [0,0,1,0],
                     [0,1,0,0] ]
           alloc = [ [0,1,0,0],
                     [1,1,0,0],
                     [0,0,1,0] ]

tests = TestList [ TestCase (False @=? isSafe total1 max1 alloc1)
                 , TestCase (True  @=? isSafe total2 max2 alloc2)
                 , TestCase (False @=? isDead total3 need3 alloc3)
                 ]
        where (total1, max1,  alloc1) = s1
              (total2, max2,  alloc2) = s2
              (total3, need3, alloc3) = s3

main = runTestTT tests
