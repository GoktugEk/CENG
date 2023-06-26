def triplets(num):
    res = []
    for i in range(1,num):
        for j in range(i+1,num):
            hypo = (i**2 + j**2)**0.5
            if hypo == int(hypo) and hypo <num:
                res.append((i,j,int(hypo)))
    return res
