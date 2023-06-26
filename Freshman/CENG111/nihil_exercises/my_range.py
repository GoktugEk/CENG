res = []
def myrange(x,y,z):
    if x>=y:
        return res
    res.append(x)
    myrange(x+z,y,z)
    return res
- item_count
a = 0
i = 0
def count_item(x,y):
    global i
    global a
    if x == y[i]:
        a += 1
    if i == len(y)-1:
        return a
    i+=1
    count_item(x,y)
    return a