def lis(l):
    old_number = 0
    old_res = 0
    res = 0
    for i in l:
	if i >= old_number:
	    res += 1
        elif old_res >= res:
            res = 0
        else:
            old_res = res
            res = 1
        old_number = i
    return max(old_res,res)
