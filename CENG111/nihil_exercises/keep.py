def keep(func,items):
    if items == []:
        return []
    if func(items[0]):
        return [items[0]] + keep(func,items[1:])
    return keep(func,items[1:])
