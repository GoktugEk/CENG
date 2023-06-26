def triangle(num):
    res = []
    for i in range(1,num+1):
        res.append(" "*(num - i ) + "*"*(2*i-1))
    return (res)
