module PE3 where

data Cell = SpaceCraft Int | Sand | Rock Int | Pit deriving (Eq, Read, Show)

type Grid = [[Cell]]
type List = [Cell]
type Coordinate = (Int, Int)

data Move = North | East | South | West | PickUp | PutDown deriving (Eq, Read, Show)

data Robot = Robot { name :: String,
                     location :: Coordinate,
                     capacity :: Int,
                     energy :: Int,
                     storage :: Int } deriving (Read, Show)

-------------------------------------------------------------------------------------------
--------------------------------- DO NOT CHANGE ABOVE -------------------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------
-------------------------------------- PART I ---------------------------------------------

isInGrid :: Grid -> Coordinate -> Bool
isInGrid grid (y,x) = row >= x && col >= y && y >=0 && x>= 0 
    where
        row = (length grid) -1
        col = (length (grid!!0))  -1

-------------------------------------------------------------------------------------------

totalCount :: Grid -> Int
totalCount [] = 0 
totalCount (f : r) = totalCountHelper f 0 + totalCount r 


totalCountHelper :: [Cell] -> Int -> Int
totalCountHelper [] num = num
totalCountHelper (Rock x : r) num = totalCountHelper r (num+x) 
totalCountHelper (_:r) num = totalCountHelper r num
-------------------------------------------------------------------------------------------

coordinatesOfPits :: Grid -> [Coordinate]
coordinatesOfPits [] = []
coordinatesOfPits grid = quickSort (coordinateCalc grid 0)

quickSort :: [Coordinate] -> [Coordinate] 
quickSort [] = []
quickSort [f] = [f]
quickSort (f:r) = quickSort (quickSortB f r []) ++ [f] ++ quickSort (quickSortS f r [])

quickSortB :: Coordinate -> [Coordinate] -> [Coordinate] -> [Coordinate]
quickSortB _ [] acc = acc
quickSortB piv (f:r) acc = if tupleComp f piv then quickSortB piv r (acc ++ [f])  else quickSortB piv r acc

quickSortS :: Coordinate -> [Coordinate] -> [Coordinate] -> [Coordinate]
quickSortS _ [] acc = acc
quickSortS piv (f:r) acc = if tupleComp piv f then quickSortS piv r (acc ++ [f])  else quickSortS piv r acc

tupleComp :: Coordinate -> Coordinate -> Bool
tupleComp (x,y) (a,b)
    | x < a = True
    | x > a = False
    | otherwise = y<b


coordinateCalc :: Grid -> Int -> [Coordinate]
coordinateCalc [] val = []
coordinateCalc (f:r) val = coordinatesOfPitsHelper f (0,val) [] ++ coordinateCalc r (val+1)

coordinatesOfPitsHelper :: [Cell] -> Coordinate -> [Coordinate] -> [Coordinate]
coordinatesOfPitsHelper [] coor lis = lis
coordinatesOfPitsHelper (Pit : r) (x , y) lis = coordinatesOfPitsHelper r (x+1 , y) (lis ++ [(x , y)]) 
coordinatesOfPitsHelper (_:r) (x,y) lis = coordinatesOfPitsHelper r ((x+1 , y)) lis 
-------------------------------------------------------------------------------------------

tracePath :: Grid -> Robot -> [Move] -> [Coordinate]
tracePath grid robot [] = []
tracePath grid robot mov = tracePathHelper grid robot mov []


isIn :: [Coordinate] -> Coordinate -> Bool
isIn [] _ = False 
isIn ((f,s):r) (x,y) = if f == x && s == y then True else isIn r (x,y)


    


tracePathHelper :: Grid -> Robot -> [Move] -> [Coordinate] -> [Coordinate]
tracePathHelper grid robot [] acc = acc
tracePathHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren,
                     storage = rstor } (f:r) acc
    |  isIn (coordinatesOfPits grid) (x,y) = tracePathHelper grid  Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren,
                     storage = rstor } r (acc ++ [(x,y)]) 
    |  ren <= 0 = tracePathHelper grid  Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren,
                     storage = rstor } r (acc ++ [(x,y)]) 
    |  f == PickUp && ren >= 5 && rstor < rcap = tracePathHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-5,
                     storage = rstor+1 } r (acc++[(x,y)])
    |  f == PickUp && ren < 5 = tracePathHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = 0,
                     storage = rstor } r (acc++[(x,y)]) 
    |  f == PutDown && ren >= 3 = tracePathHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-3,
                     storage = rstor-1 } r (acc++[(x,y)])
    |  f == PutDown && ren < 3 = tracePathHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = 0,
                     storage = rstor } r (acc++[(x,y)]) 
    |  f == North && isInGrid grid (x,y-1) = tracePathHelper grid Robot { name = rname, 
                     location = (x,y-1),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r (acc++[(x,y-1)])
    |  f == South && isInGrid grid (x,y+1) = tracePathHelper grid Robot { name = rname, 
                     location = (x,y+1),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r (acc++[(x,y+1)])
    |  f == East && isInGrid grid (x+1,y) = tracePathHelper grid Robot { name = rname, 
                     location = (x+1,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r (acc++[(x+1,y)])
    |  f == West && isInGrid grid (x-1,y) = tracePathHelper grid Robot { name = rname, 
                     location = (x-1,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r (acc++[(x-1,y)])
    |  otherwise = tracePathHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r (acc++[(x,y)])

             

                
------------------------------------- PART II ----------------------------------------------

energiseRobots :: Grid -> [Robot] -> [Robot]
energiseRobots grid [] = []
energiseRobots grid lis = energiseRobotsHelper grid lis [] (coordinateSpace grid 0)

energiseRobotsHelper :: Grid -> [Robot] -> [Robot] -> [Coordinate] -> [Robot]
energiseRobotsHelper grid [] acc _ = acc
energiseRobotsHelper grid (Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren,
                     storage = rstor }:r) acc ((xs,ys):rs) = energiseRobotsHelper grid r (acc ++ [Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = makeHundred (ren + (max 0 (100 - (abs (xs - x) + abs (ys - y))*20))) ,
                     storage = rstor }]) [(xs,ys)]

coordinateSpace :: Grid -> Int -> [Coordinate]
coordinateSpace [] val = []
coordinateSpace (f:r) val = coordinatesOfSpaceHelper f (0,val) [] ++ coordinateSpace r (val+1)

coordinatesOfSpaceHelper :: [Cell] -> Coordinate -> [Coordinate] -> [Coordinate]
coordinatesOfSpaceHelper  [] coor lis = lis
coordinatesOfSpaceHelper (SpaceCraft s : r) (x , y) lis = lis ++ [(x , y)]
coordinatesOfSpaceHelper  (_:r) (x,y) lis = coordinatesOfSpaceHelper r ((x+1 , y)) lis 

makeHundred :: Int -> Int 
makeHundred x = if x>100 then 100 else x

-------------------------------------------------------------------------------------------

applyMoves :: Grid -> Robot -> [Move] -> (Grid, Robot)
applyMoves grid robot moves = applyMovesHelper grid robot moves 


applyMovesHelper :: Grid -> Robot -> [Move]  -> (Grid,Robot)
applyMovesHelper grid robot [] = (grid, robot)
applyMovesHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren,
                     storage = rstor } (f:r)
    |  isIn (coordinatesOfPits grid) (x,y) = applyMovesHelper grid  Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r 
    |  ren <= 0 = applyMovesHelper grid  Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren,
                     storage = rstor } r 
    |  f == PickUp && ren >= 5 && rstor < rcap = applyMovesHelper (changeGrid grid (0,0) (x,y) (-1) []) Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-5,
                     storage = rstor+1 } r 
    |  f == PutDown && ren >= 3 = applyMovesHelper (changeGrid grid (0,0) (x,y) (1) []) Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-3,
                     storage = rstor-1 } r 
    |  f == PickUp && ren < 5 = applyMovesHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = 0,
                     storage = rstor } r 
    |  f == PickUp && rcap <= rstor = applyMovesHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-5,
                     storage = rstor } r 
    |  f == PutDown && ren < 3 = applyMovesHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = 0,
                     storage = rstor } r 
    |  f == North && isInGrid grid (x,y-1) = applyMovesHelper grid Robot { name = rname, 
                     location = (x,y-1),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r 
    |  f == South && isInGrid grid (x,y+1) = applyMovesHelper grid Robot { name = rname, 
                     location = (x,y+1),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r 
    |  f == East && isInGrid grid (x+1,y) = applyMovesHelper grid Robot { name = rname, 
                     location = (x+1,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r 
    |  f == West && isInGrid grid (x-1,y) = applyMovesHelper grid Robot { name = rname, 
                     location = (x-1,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r 
    |  otherwise = applyMovesHelper grid Robot { name = rname, 
                     location = (x,y),
                     capacity = rcap,
                     energy = ren-1,
                     storage = rstor } r 





changeGrid :: Grid -> Coordinate -> Coordinate ->Int -> Grid  -> Grid 
changeGrid [] coor level int acc  = reverse acc
changeGrid (f:r) (x,y) level int acc = changeGrid r (0,y+1) level int ([changeCell f (0,y) level int []] ++ acc) 

changeCell :: [Cell] -> Coordinate -> Coordinate -> Int -> [Cell] ->[Cell]
changeCell [] coor level int acc = reverse acc
changeCell (Rock amount : r) (x,y) (a,b) int acc 
    |  a == x && b ==y = changeCell r (x+1,y) (a,b) int  ([Rock (amount + int)] ++ acc) 
changeCell (SpaceCraft amount : r) (x,y) (a,b) int acc 
    |  a == x && b ==y = changeCell r (x+1,y) (a,b) int  ([SpaceCraft (amount + int)] ++ acc) 
changeCell (f:r) (x,y) level int acc = changeCell r (x+1,y) level int ([f] ++ acc )
 