-- A generic binary tree holding values of some type a. Note that a is
-- a type parameter for our tree.

data Tree a = Empty
            | Leaf a
            | Branch a (Tree a) (Tree a)
            deriving (Show)

-- Some simple trees...

t0 :: Tree Char
t0 = Empty

t1 :: Tree Char
t1 = Leaf 'a'

t2 :: Tree Char
t2 = Branch 'a' Empty (Leaf 'b')

t3 :: Tree Char
t3 = Branch 'b' (Leaf 'a') (Leaf 'c')

t4 :: Tree Char
t4 = Branch 'd' (Branch 'b' (Leaf 'a') (Leaf 'c')) Empty

-- Some elementary functions operating on trees. The toList function
-- returns a list of all values stored in a tree while the mapTree
-- function maps a function over a tree, returning a new tree.

toList :: Tree a -> [a]
toList Empty = []
toList (Leaf x) = [x]
toList (Branch x l r) = toList l ++ [x] ++ toList r

mapTree :: (a -> b) -> Tree a -> Tree b
mapTree f Empty = Empty
mapTree f (Leaf x) = Leaf (f x)
mapTree f (Branch x l r) = Branch (f x) (mapTree f l) (mapTree f r)

main = print $ toList $ mapTree succ t4
