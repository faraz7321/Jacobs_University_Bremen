{-
            .-  0                        if n == 0 
            |
   fib(n) = +-  1                        if n == 1
            |
            +-  fib(n-1) + fib(n-2)      if n > 1
            |
            '-  fib(-n)                  if n < 0
-}

module Main (main) where

import Test.HUnit

-- Definition of fib using pattern matching.
fib1 :: Integer -> Integer
fib1 0 = 0
fib1 1 = 1
fib1 n = if n > 1 then fib1 (n-1) + fib1 (n-2) else fib1 (-n)

-- Definition of fib using guards.
fib2 :: Integer -> Integer
fib2 n
  | n == 0    = 0
  | n == 1    = 1
  | n > 1     = fib2 (n-1) + fib2 (n-2)
  | otherwise = fib2 (-n)

-- Definition of fib using pattern matching and guards.
fib3 :: Integer -> Integer
fib3 0 = 0
fib3 1 = 1
fib3 n
  | n > 1     = fib3 (n-1) + fib3 (n-2)
  | otherwise = fib3 (-n)

-- Definition of fib using case expressions.
fib4 :: Integer -> Integer
fib4 n = case (n, n>1) of (0, _)     -> 0
                          (1, _)     -> 1
                          (_, True)  -> fib4 (n-1) + fib4 (n-2)
                          (_, False) -> fib4 (-n)

fibTests fib = TestList [ fib 0 ~?= 0
                        , fib 1 ~?= 1
                        , fib (-1) ~?= 1
                        , fib 2 ~?= 1   -- fib(2) = fib(1) + fib(0) = 1 + 0 = 1
                        , fib (-2) ~?= 1
                        , fib 3 ~?= 2   -- fib(3) = fib(2) + fib(1) = 1 + 1 = 2
                        , fib 4 ~?= 3 
                        , fib 5 ~?= 5 
                        , fib 6 ~?= 8 
                        , fib 7 ~?= 13 
                        , fib 8 ~?= 21
                        , fib (-8) ~?= 21
                        ]
                 
main = runTestTT $ TestList (map fibTests [fib1, fib2, fib3, fib4])
