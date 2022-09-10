isLongYear :: Int -> Bool
isLongYear year
  | (year + (year `div` 4) - (year `div` 100) + (year `div` 400)) `mod` 7 == 4 = True
  | ((year - 1) + ((year - 1) `div` 4) - ((year - 1) `div` 100) + ((year - 1) `div` 400)) `mod` 7 == 3 = True
  | otherwise = False