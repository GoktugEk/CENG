#the3n1p
def the3N1P(num):
    res = []
    while True:
        if num == 1:
            res.append(1)
            break
        elif num % 2 == 0:
            res.append(num)
            num /= 2
        else:
            res.append(num)
            num = num*3 +1
    return len(res)
