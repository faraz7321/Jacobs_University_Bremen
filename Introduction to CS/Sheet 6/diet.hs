module Main (main) where

import Test.HUnit

-- The function diet implements the three diet rules directly.
diet :: Bool -> Bool -> Bool -> Bool
diet b f i = undefined

-- The function diet' implements the simplified diet formula.
diet' :: Bool -> Bool -> Bool -> Bool
diet' b f i = undefined

-- The function truthTable takes a function as an argument and returns
-- a list where each element is a 4-tuple representing three input
-- value passed to the function followed by the function's result.
truthTable :: (Bool -> Bool -> Bool -> Bool) -> [(Bool, Bool, Bool, Bool)]
truthTable f = undefined

-- Test whether the two truth tables returned are the same (which is
-- not a very sharp test but I do not want to reveal too many details).
-- You may want to add your own test cases...
dietTests = TestList [truthTable diet ~?= truthTable diet']

main = runTestTT dietTests