module PE4 where

import Data.Maybe -- up to you if you want to use it or not

-- Generic DictTree definition with two type arguments
data DictTree k v = Node [(k, DictTree k v)] | Leaf v deriving Show

-- Lightweight Char wrapper as a 'safe' Digit type
newtype Digit = Digit Char deriving (Show, Eq, Ord) -- derive equality and comparison too!

-- Type aliases
type DigitTree = DictTree Digit String
type PhoneNumber = [Digit]


---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


----------
-- Part I:
-- Some Maybe fun! Basic practice with an existing custom datatype.

-- toDigit: Safely convert a character to a digit
toDigit :: Char -> Maybe Digit
toDigit '0' = Just (Digit '0')
toDigit '1' = Just (Digit '1')
toDigit '2' = Just (Digit '2')
toDigit '3' = Just (Digit '3')
toDigit '4' = Just (Digit '4')
toDigit '5' = Just (Digit '5')
toDigit '6' = Just (Digit '6')
toDigit '7' = Just (Digit '7')
toDigit '8' = Just (Digit '8')
toDigit '9' = Just (Digit '9')
toDigit _ = Nothing

digitExt :: Maybe Digit -> [Digit]
digitExt Nothing = []
digitExt (Just a) = [a]


toStr :: Digit -> Char
toStr (Digit '0') = '0' 
toStr (Digit '1') = '1' 
toStr (Digit '2') = '2' 
toStr (Digit '3') = '3' 
toStr (Digit '4') = '4' 
toStr (Digit '5') = '5' 
toStr (Digit '6') = '6' 
toStr (Digit '7') = '7' 
toStr (Digit '8') = '8' 
toStr (Digit '9') = '9'
toStr _ = 'x'


-- toDigits: Safely convert a bunch of characters to a list of digits.
--           Particularly, an empty string should fail.
toDigits :: String -> Maybe PhoneNumber
toDigits st = toDigitsHelper st []


toDigitsHelper :: String -> [Digit] -> Maybe PhoneNumber
toDigitsHelper [] [] = Nothing
toDigitsHelper [] acc = Just acc
toDigitsHelper (f:r) acc 
    | digitExt (toDigit f) == [] = Nothing
    | otherwise = toDigitsHelper r (acc ++ digitExt (toDigit f))


digitsExt :: Maybe PhoneNumber -> PhoneNumber
digitsExt Nothing = []
digitsExt (Just a) = a

-----------
-- Part II:
-- Some phonebook business.

-- numContacts: Count the number of contacts in the phonebook...
numContacts :: DigitTree -> Int
numContacts (Node []) = 0
numContacts (Leaf _) = 1
numContacts (Node (f:r)) = 0 + numContacts (snd f) + (numContacts (Node r))
    
-- getContacts: Generate the contacts and their phone numbers in order given a tree. 
getContacts :: DigitTree -> [(PhoneNumber, String)]
getContacts tree = getContactsHelper tree [] 

getContactsHelper :: DigitTree -> String -> [(PhoneNumber, String)]
getContactsHelper (Node []) str = [] 
getContactsHelper (Leaf x) str  = [(digitsExt (toDigits str),x)]
getContactsHelper (Node (f:r)) str = getContactsHelper (snd f) (str ++ [(toStr (fst f))])  ++ getContactsHelper (Node r) (str)

-- autocomplete: Create an autocomplete list of contacts given a prefix
-- e.g. autocomplete "32" areaCodes -> 
--      [([Digit '2'], "Adana"), ([Digit '6'], "Hatay"), ([Digit '8'], "Osmaniye")]
autocomplete :: String -> DigitTree -> [(PhoneNumber, String)]
autocomplete [] _ = []
autocomplete str tree 
    | digitsExt (toDigits str) == [] = []
    | otherwise = autocompleteHelper str (getContacts tree)




autocompleteHelper :: String -> [(PhoneNumber, String)] -> [(PhoneNumber, String)]
autocompleteHelper str [] = []
autocompleteHelper str ((f,s):r)
    | isPref str f = [(giveSuff str f,s)] ++ autocompleteHelper str r 
    | otherwise = autocompleteHelper str r 


isPref :: String -> PhoneNumber -> Bool
isPref [] _ = True
isPref _ [] = False
isPref (f:r) (a:b) = if f == toStr a then isPref r b else False

giveSuff :: String -> PhoneNumber -> PhoneNumber
giveSuff [] res = res
giveSuff (f:r) (a:b) = giveSuff r b 


-----------
-- Example Trees
-- Two example trees to play around with, including THE exampleTree from the text. 
-- Feel free to delete these or change their names or whatever!

exampleTree :: DigitTree
exampleTree = Node [
    (Digit '1', Node [
        (Digit '3', Node [
            (Digit '7', Node [
                (Digit '8', Leaf "Jones")])]),
        (Digit '5', Leaf "Steele"),
        (Digit '9', Node [
            (Digit '1', Leaf "Marlow"),
            (Digit '2', Node [
                (Digit '3', Leaf "Stewart")])])]),
    (Digit '3', Leaf "Church"),
    (Digit '7', Node [
        (Digit '2', Leaf "Curry"),
        (Digit '7', Leaf "Hughes")])]

areaCodes :: DigitTree
areaCodes = Node [
    (Digit '3', Node [
        (Digit '1', Node [
            (Digit '2', Leaf "Ankara")]),
        (Digit '2', Node [
            (Digit '2', Leaf "Adana"),
            (Digit '6', Leaf "Hatay"),
            (Digit '8', Leaf "Osmaniye")])]),
    (Digit '4', Node [
        (Digit '6', Node [
            (Digit '6', Leaf "Artvin")])])]

