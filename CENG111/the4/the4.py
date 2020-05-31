def islist(l): #if given input is a list, returns true
    return type(l) == list
def isvalve(v): #checking given list is a valve or not.If it is,gives true
    return len(v) == 2 and type(v[1]) == int
def highest_valve_time(tree):#Gives the highest volume cup of a tree.
    stack = []
    res = []
    stack.append(tree)
    while stack != []:
        sub_tree = stack[-1]
        stack.pop()
        for i in sub_tree:
            if type(i) == int:
                res.append(i)
            elif type(i) == list:
                stack.append(i)
    return max(res)
        
def valve_under_tree(tree): #Gives the valve names under a tree.
    if isvalve(tree):
        return []
    stack = []
    res = []
    stack.append(tree)
    while stack != []:
        sight_tree = stack[-1]
        stack.pop()
        for i in sight_tree:
            if type(i) == str:
                res.append(i)
            elif isvalve(i):
                res.append(i[0])
            elif type(i) == list:
                stack.append(i)
    res.remove(tree[0])
    return res    
        
def find_trees(tree):#Gives the all trees under a tree.
    if isvalve(tree):
        return [tree]
    stack = []
    res = []
    stack.append(tree)
    while stack != []:
        element = stack[-1]
        stack.pop()
        for i in element:
            if isvalve(i):
                res.append(i)
            elif type(i) == list:
                res.append(i)
                stack.append(i)    
    return [tree]+res

def the_tree_starts_with(all,name):
    for i in all:
        if i[0] == name:
            return i

def minimizing_valve_number(subres,trees):
    for j in subres:
        the_tree = the_tree_starts_with(trees,j)
        valves = valve_under_tree(the_tree)
        for k in valves:
            if subres.count(k) == 1:
                subres.remove(k)
    return subres

def chalchiuhtlicue(tree):
    trees = find_trees(tree)
    maximum = highest_valve_time(tree)
    res = []
    for i in range(maximum):
        res.append([])
    for i in trees:
        high = highest_valve_time(i)
        res[high-1].append(i[0])
    for i in range(len(res)):
        res[i] = minimizing_valve_number(res[i],trees)
    return res

