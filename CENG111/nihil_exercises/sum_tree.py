def datum(x):
    return x[0]
def left_child(x):
    return x[1]
def right_child(x):
    return x[2]
def isempty(t):
    return t==[]
def sum_tree(t):
    if isempty(t):
        return 0
    return int(datum(t)) + sum_tree(left_child(t)) + sum_tree(right_child(t))