def sum_numbers(l):
    if l == []:
        return 0
    elif type(l[0]) in (int,float,long):
        return l[0]+ sum_numbers(l[1:])
    else:
        return  sum_numbers(l[1:])
