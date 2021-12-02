-- A Date type using record syntax, deriving a show function to
-- convert values to printable strings.

data Date = Date { year :: Int
                 , month :: Int
                 , day :: Int
                 }
          deriving (Show)

-- A Gender type using three data constructors representing
-- alternatives.

data Gender = Female | Male | Divers
            deriving (Show)

-- An Academic type where an academic is considered either a student
-- or a professor using record syntax. The Maybe type (predefined in
-- Haskell allows us to model optional values.

data Academic = Student { name :: String
                        , birthday :: Date
                        , gender :: Gender
                        , major :: String
                        , advisor :: Maybe Academic
                        }
              | Professor { name :: String
                          , birthday :: Date
                          , gender :: Gender
                          }
              deriving (Show)

-- The concrete values, bart is a professor and joe a student. Both
-- are of type Academic.

bart :: Academic
bart = Professor { name = "Bart Wisdom"
                 , birthday = (Date { year = 1966, month = 02, day = 07})
                 , gender = Male
                 }

joe :: Academic
joe = Student { name = "Joe Sample"
              , birthday = (Date { year = 2021, month = 11, day = 05})
              , gender = Divers
              , major = "CS"
              , advisor = Just bart
              }

-- The record syntax automatically gives us functions to access the
-- different fields of a type. Here is how you can get all names of a
-- list of academics.

allNames :: [Academic] -> [String]
allNames xs = map name xs

main = print $ allNames [joe, bart]
