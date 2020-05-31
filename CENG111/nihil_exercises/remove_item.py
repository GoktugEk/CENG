def remove_item(x,y):
    if y == []:
        return []
    elif x == y[0]:
        return remove_item(x,y[1:])
    else:
        return [y[0]] + remove_item(x,y[1:])
