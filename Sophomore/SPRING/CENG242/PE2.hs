module PE2 where
import Data.List

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

--------------------------
-- Part I: Time to inf up!

-- naturals: The infinite list of natural numbers. That's it!
naturals :: [Integer]
naturals = 0 : map (+1) naturals

-- interleave: Interleave two lists, cutting off on the shorter list.
interleave :: [a] -> [a] -> [a]
interleave _ [] = []
interleave [] _ = []
interleave (f:r) (f2:r2) = [f,f2] ++ interleave r r2

multby1 :: [Integer] -> [Integer]
multby1 [] = []
multby1 (f:r) 
    | f == 0 = multby1 r
    | otherwise = [f*(-1)] ++ multby1 r

-- integers: The infinite list of integers. Ordered as [0, -1, 1, -2, 2, -3, 3, -4, 4...].
integers :: [Integer]
integers = interleave naturals (multby1 naturals)

--------------------------------
-- Part II: SJSON Prettification

splitOnHelper :: Char -> String -> String -> (String, String)
splitOnHelper delim [] acc = (acc, "")
splitOnHelper delim (f:r) acc
    | f == delim = (acc, r)
    | otherwise = splitOnHelper delim r (acc ++ [f])


-- splitOn: Split string on first occurence of character.
splitOn :: Char -> String -> (String, String)
splitOn delim str = splitOnHelper delim str "" 


tokenizeHelper :: String -> [String] -> [String]
tokenizeHelper [] acc = acc
tokenizeHelper (f:r) acc 
    | f == '{'  = tokenizeHelper r (acc ++ [[f]])
    | f == '}'  = tokenizeHelper r (acc ++ [[f]])
    | f == ':'  = tokenizeHelper r (acc ++ [[f]])
    | f == ','  = tokenizeHelper r (acc ++ [[f]])
    | f == '\'' = tokenizeHelper (snd (splitOn '\'' r)) (acc ++ [(fst (splitOn '\'' r))])
    | otherwise = tokenizeHelper r acc
    
    

-- tokenizeS: Transform an SJSON string into a list of tokens.
tokenizeS :: String -> [String]
tokenizeS str = tokenizeHelper str []


manipulator :: Integer -> String
manipulator 0 = []
manipulator (-1) = []
manipulator int = "    " ++ manipulator (int-1)


prettifyHelper :: [String] -> String -> Integer-> String
prettifyHelper [] acc _ = acc
prettifyHelper (f:r) acc int
    | f == "{" = prettifyHelper r (acc ++ "{\n" ++ (manipulator (int+1))) (int+1)
    | f == "}" = prettifyHelper r (acc ++ "\n" ++ (manipulator (int -1)) ++ "}") (int-1)
    | f == ":" = prettifyHelper r (acc ++ ": ") (int)
    | f == "," = prettifyHelper r (acc ++ ",\n" ++ (manipulator int)) int
    | otherwise = prettifyHelper r (acc ++ "'" ++ f ++ "'")  int


-- prettifyS: Prettify SJSON, better tokenize first!
prettifyS :: String -> String
prettifyS s = prettifyHelper (tokenizeS s) "" 0

-- Good luck to you, friend and colleague!

