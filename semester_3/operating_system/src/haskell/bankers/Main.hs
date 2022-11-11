module Main where

import Bankers

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

main = do
  print "Checking s1:"
  print $ isSafe total1 max1 alloc1
  print "Checking s2:"
  print $ isSafe total2 max2 alloc2
      where (total1, max1, alloc1) = s1
            (total2, max2, alloc2) = s2

